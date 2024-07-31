using System.Collections;
using System.Collections.Generic;
using Unity.EditorCoroutines.Editor;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    public class WFCGeneration : EditorWindow
    {
        [SerializeField]
        private VisualTreeAsset m_VisualTreeAsset = default;

        private ObjectField nodeField;
        private UnsignedIntegerField nodeCountField;
        private FloatField nodeSizeField;
        private UnsignedIntegerField seedField;
        private EnumFlagsField axesField;
        private EnumField expansionModeField;
        private Vector3Field startPosition;
        private Toggle frameByFrameToggle;

        private IWFCNode wfcNode;

        struct NodeInfo
        {
            public Vector3 position;
            public LevelGenerationDirection direction;
        }

        [MenuItem("PCG/Wave Function Collapse Generation")]
        public static void ShowExample()
        {
            WFCGeneration wnd = GetWindow<WFCGeneration>();
            wnd.titleContent = new GUIContent("Wave Function Collapse Generation");
        }

        private void ValidateNodeField(ChangeEvent<Object> changeEvent)
        {
            if (changeEvent.newValue == null)
            {
                return;
            }

            GameObject newGameObject = changeEvent.newValue as GameObject;

            if (newGameObject != null && newGameObject.TryGetComponent(out wfcNode))
            {
                return;
            }

            Debug.LogError($"{newGameObject.name} has no component that inherits from IWFCNode");
            nodeField.value = changeEvent.previousValue; //this will call the event again
        }

        public void CreateGUI()
        {
            // Instantiate UXML
            VisualElement uxmlElements = m_VisualTreeAsset.Instantiate();
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
            generateButton.clicked += SpawnObject;

            nodeField.RegisterValueChangedCallback(ValidateNodeField);
        }

        private void SpawnObject()
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

        void AddNode(Transform nodeParent, Vector3 nodePosition, LevelGenerationDirection adjacentNodes)
        {
            UnityEngine.Vector3 position = PCGEngine2Unity.PCGEngineVectorToUnity(nodePosition);
            IWFCNode node = Instantiate(wfcNode.gameObject, nodeParent).GetComponent<IWFCNode>();
            node.transform.position = position;
            node.SetAdjacentNodes(adjacentNodes);
        }

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
