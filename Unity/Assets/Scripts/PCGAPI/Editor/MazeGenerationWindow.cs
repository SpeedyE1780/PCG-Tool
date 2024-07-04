using System.Collections;
using System.Collections.Generic;
using Unity.EditorCoroutines.Editor;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    public class MazeGenerationWindow : EditorWindow
    {
        [SerializeField]
        private VisualTreeAsset m_VisualTreeAsset = default;

        private ObjectField nodeField;
        private Vector2IntField gridSizeField;
        private FloatField nodeSizeField;
        private UnsignedIntegerField seedField;
        private EnumField mazeAlgorithmField;
        private Toggle delayedInvoke;
        private Toggle frameByFrameToggle;

        private Transform nodeParent;
        private WFCNode node;
        private float nodeSize;

        struct NodeInfo
        {
            public int x;
            public int y;
            public Direction direction;
        }

        [MenuItem("PCG/Maze Generation")]
        public static void ShowExample()
        {
            MazeGenerationWindow wnd = GetWindow<MazeGenerationWindow>();
            wnd.titleContent = new GUIContent("Maze Generation");
        }

        public void CreateGUI()
        {
            // Instantiate UXML
            VisualElement uxmlElements = m_VisualTreeAsset.Instantiate();
            rootVisualElement.Add(uxmlElements);

            nodeField = rootVisualElement.Q<ObjectField>("NodeField");
            gridSizeField = rootVisualElement.Q<Vector2IntField>("GridSize");
            nodeSizeField = rootVisualElement.Q<FloatField>("NodeSize");
            seedField = rootVisualElement.Q<UnsignedIntegerField>("Seed");
            mazeAlgorithmField = rootVisualElement.Q<EnumField>("MazeAlgorithm");
            frameByFrameToggle = rootVisualElement.Q<Toggle>("FrameByFrame");
            delayedInvoke = rootVisualElement.Q<Toggle>("DelayedInvoke");

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
            nodeSize = nodeSizeField.value;
            Vector2Int gridSize = gridSizeField.value;

            if (node == null)
            {
                Debug.LogWarning("Node not set");
                return;
            }

            if (gridSize.x == 0 || gridSize.y == 0)
            {
                Debug.LogWarning("Grid needs to have x and y > 0");
                return;
            }

            if (nodeSize == 0)
            {
                Debug.LogWarning("Node size not set");
                return;
            }

            PCGEngine.SetSeed(seedField.value);

            nodeParent = new GameObject("MAZE").transform;

            if (frameByFrameToggle.value)
            {
                List<NodeInfo> nodes = new List<NodeInfo>();

                void AddNodeInfo(int x, int y, Direction adjacentNodes)
                {
                    nodes.Add(new NodeInfo()
                    {
                        x = x,
                        y = y,
                        direction = adjacentNodes
                    });
                }

                PCGEngine.GenerateMaze(gridSize.x, gridSize.y, delayedInvoke.value, (MazeAlgorithm)mazeAlgorithmField.value, AddNodeInfo);

                if (delayedInvoke.value)
                {
                    EditorCoroutineUtility.StartCoroutine(DelayedGeneration(nodes), this);
                }
                else
                {
                    EditorCoroutineUtility.StartCoroutine(Generation(nodes), this);
                }
            }
            else
            {
                PCGEngine.GenerateMaze(gridSize.x, gridSize.y, true, (MazeAlgorithm)mazeAlgorithmField.value, AddMazeNode);
            }
        }

        private void AddMazeNode(int x, int y, Direction adjacentNodes)
        {
            UnityEngine.Vector3 position = new UnityEngine.Vector3(x * nodeSize, 0, y * nodeSize);
            WFCNode n = Instantiate(node, nodeParent);
            n.transform.position = position;
            n.SetNeighbors(adjacentNodes);
        }

        private IEnumerator DelayedGeneration(List<NodeInfo> nodes)
        {
            foreach (NodeInfo node in nodes)
            {
                AddMazeNode(node.x, node.y, node.direction);
                yield return null;
            }
        }

        private IEnumerator Generation(List<NodeInfo> nodes)
        {
            Dictionary<Vector2, WFCNode> spawnedNodes = new Dictionary<Vector2, WFCNode>();

            foreach (NodeInfo nodeInfo in nodes)
            {
                Vector2 key = new Vector2(nodeInfo.x, nodeInfo.y);

                if (spawnedNodes.ContainsKey(key))
                {
                    spawnedNodes[key].SetNeighbors(nodeInfo.direction);
                }
                else
                {
                    UnityEngine.Vector3 position = new UnityEngine.Vector3(nodeInfo.x * nodeSize, 0, nodeInfo.y * nodeSize);
                    WFCNode n = Instantiate(node, nodeParent);
                    n.transform.position = position;
                    n.SetNeighbors(nodeInfo.direction);
                    spawnedNodes.Add(key, n);
                }

                yield return null;
            }
        }
    }
}
