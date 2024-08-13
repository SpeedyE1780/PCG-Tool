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
    public class WFCGeneration : EditorWindow
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
            public Vector3 position;
            public LevelGenerationDirection direction;
        }

        /// <summary>
        /// Adds menu item to Unity Editor to open window
        /// </summary>
        [MenuItem("PCG/Wave Function Collapse Generation")]
        public static void OpenWindow()
        {
            WFCGeneration wnd = GetWindow<WFCGeneration>();
            wnd.titleContent = new GUIContent("Wave Function Collapse Generation");
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

                void AddNodeInfo(Vector3 nodePosition, LevelGenerationDirection adjacentNodes)
                {
                    nodes.Add(new NodeInfo()
                    {
                        position = nodePosition,
                        direction = adjacentNodes
                    });
                }

                PCGEngine.WaveFunctionCollapseGeneration(ref generationParameters, (ExpansionMode)expansionModeField.value, (Axis)axesField.value, AddNodeInfo);
                EditorCoroutineUtility.StartCoroutine(SpawnLevel(nodes, nodeParent), this);
            }
            else
            {
                void AddWFCNode(Vector3 nodePosition, LevelGenerationDirection adjacentNodes)
                {
                    AddNode(nodeParent, nodePosition, adjacentNodes);
                }

                PCGEngine.WaveFunctionCollapseGeneration(ref generationParameters, (ExpansionMode)expansionModeField.value, (Axis)axesField.value, AddWFCNode);
            }
        }

        /// <summary>
        /// Spawn node in world space
        /// </summary>
        /// <param name="nodeParent">Node parent</param>
        /// <param name="nodePosition">Node world position</param>
        /// <param name="adjacentNodes">Adjacent nodes bit mask</param>
        void AddNode(Transform nodeParent, Vector3 nodePosition, LevelGenerationDirection adjacentNodes)
        {
            UnityEngine.Vector3 position = PCGEngine2Unity.PCGEngineVectorToUnity(nodePosition);
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
            foreach (NodeInfo node in nodes)
            {
                AddNode(nodeParent, node.position, node.direction);
                yield return null;
            }
        }
    }
}
