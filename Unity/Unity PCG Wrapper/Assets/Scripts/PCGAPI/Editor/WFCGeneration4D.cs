using System.Collections;
using System.Collections.Generic;
using Unity.EditorCoroutines.Editor;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    /// <summary>
    /// Class used to generate levels using wave function collapse
    /// </summary>
    public class WFCGeneration4D : EditorWindow
    {
        [SerializeField, Tooltip("Wave Function Collapse Generation Window UXML File")]
        private VisualTreeAsset windowUXML = default;

        private ObjectField nodeField;
        private UnsignedIntegerField nodeCountField;
        private FloatField nodeSizeField;
        private UnsignedIntegerField seedField;
        private EnumFlagsField axesField;
        private EnumField expansionModeField;
        private Vector3Field startPosition;
        private Toggle frameByFrameToggle;

        private IWFCNode wfcNode;

        /// <summary>
        /// Struct representing node info in world
        /// </summary>
        struct NodeInfo
        {
            public Vector4 position;
            public LevelGenerationDirection direction;
        }

        /// <summary>
        /// Adds menu item to Unity Editor to open window
        /// </summary>
        [MenuItem("PCG/Wave Function Collapse 4D Generation")]
        public static void OpenWindow()
        {
            WFCGeneration4D wnd = GetWindow<WFCGeneration4D>();
            wnd.titleContent = new GUIContent("Wave Function Collapse 4D Generation");
        }

        /// <summary>
        /// Called when window is created
        /// </summary>
        public void CreateGUI()
        {
            VisualElement uxmlElements = windowUXML.Instantiate();
            rootVisualElement.Add(uxmlElements);

            nodeField = rootVisualElement.Q<ObjectField>("Node");
            nodeCountField = rootVisualElement.Q<UnsignedIntegerField>("Count");
            nodeSizeField = rootVisualElement.Q<FloatField>("Size");
            seedField = rootVisualElement.Q<UnsignedIntegerField>("Seed");
            startPosition = rootVisualElement.Q<Vector3Field>("StartPosition");
            axesField = rootVisualElement.Q<EnumFlagsField>("Axes");
            expansionModeField = rootVisualElement.Q<EnumField>("ExpansionMode");
            frameByFrameToggle = rootVisualElement.Q<Toggle>("FramebyFrame");

            var generateButton = rootVisualElement.Q<Button>("GenerateButton");
            generateButton.clicked += GenerateLevel;

            nodeField.RegisterValueChangedCallback(changeEvent => WindowHelper.ValidateGameObjectField(ref wfcNode, nodeField, changeEvent));
        }

        /// <summary>
        /// Generate level using selected node and axes using Wave Function Collapse
        /// </summary>
        private void GenerateLevel()
        {
            static void Log(string msg)
            {
                Debug.Log(msg);
            }

            PCGEngine.SetLoggingFunction(Log);

            uint nodeCount = nodeCountField.value;
            float size = nodeSizeField.value;

            if (wfcNode == null)
            {
                Debug.LogWarning("Node not set");
                return;
            }

            if (nodeCount == 0)
            {
                Debug.LogWarning("Node count is zero");
                return;
            }

            if (size == 0)
            {
                Debug.LogWarning("Node size not set");
                return;
            }

            PCGEngine.SetSeed(seedField.value);

            Transform nodeParent = new GameObject("Wave Function Collapse Generation").transform;

            GenerationParameters generationParameters = new GenerationParameters()
            {
                count = nodeCount,
                size = size,
                startPoint = PCGEngine2Unity.UnityToPCGEngineVector(startPosition.value)
            };

            if (frameByFrameToggle.value)
            {
                List<NodeInfo> nodes = new List<NodeInfo>();

                void AddNodeInfo(Vector4 nodePosition, LevelGenerationDirection adjacentNodes)
                {
                    nodes.Add(new NodeInfo()
                    {
                        position = nodePosition,
                        direction = adjacentNodes
                    });
                }

                PCGEngine.WaveFunctionCollapse4DGeneration(generationParameters, (ExpansionMode)expansionModeField.value, (Axis)axesField.value, AddNodeInfo);
                EditorCoroutineUtility.StartCoroutine(SpawnLevel(nodes, nodeParent), this);
            }
            else
            {
                Dictionary<float, Transform> dimensions = new Dictionary<float, Transform>();

                void AddWFCNode(Vector4 nodePosition, LevelGenerationDirection adjacentNodes)
                {
                    if (!dimensions.TryGetValue(nodePosition.w, out Transform parent))
                    {
                        parent = new GameObject($"Dimension {nodePosition.w}").transform;
                        parent.SetParent(nodeParent);
                        dimensions[nodePosition.w] = parent;
                    }

                    AddNode(parent, nodePosition, adjacentNodes);
                }

                PCGEngine.WaveFunctionCollapse4DGeneration(generationParameters, (ExpansionMode)expansionModeField.value, (Axis)axesField.value, AddWFCNode);

                foreach (var dimension in dimensions.Values)
                {
                    dimension.gameObject.SetActive(false);
                }

                dimensions[0].gameObject.SetActive(true);
            }
        }

        /// <summary>
        /// Spawn node in world space
        /// </summary>
        /// <param name="nodeParent">Node parent</param>
        /// <param name="nodePosition">Node world position</param>
        /// <param name="adjacentNodes">Adjacent nodes bit mask</param>
        void AddNode(Transform nodeParent, Vector4 nodePosition, LevelGenerationDirection adjacentNodes)
        {
            UnityEngine.Vector4 position = PCGEngine2Unity.PCGEngineVectorToUnity(nodePosition);
            IWFCNode node = WindowHelper.SpawnGameObject(wfcNode.gameObject, nodeParent).GetComponent<IWFCNode>();
            node.transform.position = position;
            node.SetAdjacentNodes(adjacentNodes);
        }

        /// <summary>
        /// Spawn nodes in world frame by frame
        /// </summary>
        /// <param name="nodes">List of nodes to spawn</param>
        /// <param name="nodeParent">Node parents</param>
        IEnumerator SpawnLevel(List<NodeInfo> nodes, Transform nodeParent)
        {
            Dictionary<float, Transform> dimensions = new Dictionary<float, Transform>();
            float currentDimension = 0;
            Transform currentParent = new GameObject("Dimension 0").transform;
            currentParent.SetParent(nodeParent);
            dimensions.Add(currentDimension, currentParent);

            foreach (NodeInfo node in nodes)
            {
                if (nodeParent == null)
                {
                    Debug.LogError("Node parent was destroyed ending generation early");
                    yield break;
                }

                if (!dimensions.TryGetValue(node.position.w, out Transform parent))
                {
                    parent = new GameObject($"Dimension {node.position.w}").transform;
                    parent.SetParent(nodeParent);
                    dimensions[node.position.w] = parent;
                }

                if (node.position.w != currentDimension)
                {
                    currentDimension = node.position.w;
                    currentParent.gameObject.SetActive(false);
                    currentParent = parent;
                    currentParent.gameObject.SetActive(true);
                }

                AddNode(parent, node.position, node.direction);
                yield return null;
            }

            currentParent.gameObject.SetActive(false);
            dimensions[0].gameObject.SetActive(true);
            Debug.Log("All nodes spawned");
        }
    }
}
