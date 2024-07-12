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

        private Transform nodeParent;
        private WFCNode node;

        struct NodeInfo
        {
            public Vector3 position;
            public Direction direction;
        }

        [MenuItem("PCG/Wave Function Collapse Generation")]
        public static void ShowExample()
        {
            WFCGeneration wnd = GetWindow<WFCGeneration>();
            wnd.titleContent = new GUIContent("Wave Function Collapse Generation");
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
        }

        private void SpawnObject()
        {
            static void Log(string msg)
            {
                Debug.Log(msg);
            }

            PCGEngine.SetLoggingFunction(Log);

            node = nodeField.value as WFCNode;
            uint nodeCount = nodeCountField.value;
            float size = nodeSizeField.value;

            if (node == null)
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

            nodeParent = new GameObject("Multi Dimensional Generation").transform;

            GenerationParameters generationParameters = new GenerationParameters()
            {
                count = nodeCount,
                size = size,
                startPoint = PCGEngine2Unity.UnityToPCGEngineVector(startPosition.value)
            };

            if (frameByFrameToggle.value)
            {
                List<NodeInfo> nodes = new List<NodeInfo>();

                void AddNodeInfo(Vector3 nodePosition, Direction adjacentNodes)
                {
                    nodes.Add(new NodeInfo()
                    {
                        position = nodePosition,
                        direction = adjacentNodes
                    });
                }

                PCGEngine.WaveFunctionCollapseGeneration(ref generationParameters, (ExpansionMode)expansionModeField.value, (Axis)axesField.value, AddNodeInfo);
                EditorCoroutineUtility.StartCoroutine(SpawnLevel(nodes), this);
            }
            else
            {
                PCGEngine.WaveFunctionCollapseGeneration(ref generationParameters, (ExpansionMode)expansionModeField.value, (Axis)axesField.value, AddNode);
            }
        }

        void AddNode(Vector3 nodePosition, Direction adjacentNodes)
        {
            UnityEngine.Vector3 position = PCGEngine2Unity.PCGEngineVectorToUnity(nodePosition);
            WFCNode n = Instantiate(node, nodeParent);
            n.transform.position = position;
            n.SetAdjacentNodes(adjacentNodes);
        }

        IEnumerator SpawnLevel(List<NodeInfo> nodes)
        {
            foreach (NodeInfo node in nodes)
            {
                AddNode(node.position, node.direction);
                yield return null;
            }
        }
    }
}
