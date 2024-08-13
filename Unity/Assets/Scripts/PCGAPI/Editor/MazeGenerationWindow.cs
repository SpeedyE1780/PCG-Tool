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
    /// Class used to create maze
    /// </summary>
    public class MazeGenerationWindow : EditorWindow
    {
        [SerializeField, Tooltip("Maze Generation Window UXML File")]
        private VisualTreeAsset windowUXML = default;

        private ObjectField nodeField;
        private Vector2IntField gridSizeField;
        private FloatField nodeSizeField;
        private UnsignedIntegerField seedField;
        private EnumField mazeAlgorithmField;
        private Toggle delayedInvoke;
        private Toggle frameByFrameToggle;
        private IMazeNode mazeNode;

        /// <summary>
        /// Contains 2D grid node info
        /// </summary>
        struct NodeInfo
        {
            public int x;
            public int y;
            public float size;
            public MazeDirection adjacentNodes;
        }

        /// <summary>
        /// Adds menu item to Unity Editor to open window
        /// </summary>
        [MenuItem("PCG/Maze Generation")]
        public static void OpenWindow()
        {
            MazeGenerationWindow wnd = GetWindow<MazeGenerationWindow>();
            wnd.titleContent = new GUIContent("Maze Generation");
        }

        /// <summary>
        /// Called when window is created
        /// </summary>
        public void CreateGUI()
        {
            VisualElement uxmlElements = windowUXML.Instantiate();
            rootVisualElement.Add(uxmlElements);

            nodeField = rootVisualElement.Q<ObjectField>("NodeField");
            gridSizeField = rootVisualElement.Q<Vector2IntField>("GridSize");
            nodeSizeField = rootVisualElement.Q<FloatField>("NodeSize");
            seedField = rootVisualElement.Q<UnsignedIntegerField>("Seed");
            mazeAlgorithmField = rootVisualElement.Q<EnumField>("MazeAlgorithm");
            frameByFrameToggle = rootVisualElement.Q<Toggle>("FrameByFrame");
            delayedInvoke = rootVisualElement.Q<Toggle>("DelayedInvoke");

            var generateButton = rootVisualElement.Q<Button>("GenerateButton");
            generateButton.clicked += GenerateMaze;

            nodeField.RegisterValueChangedCallback((changeEvent) => WindowHelper.ValidateObjectField(ref mazeNode, nodeField, changeEvent));
        }

        /// <summary>
        /// Generate maze
        /// </summary>
        private void GenerateMaze()
        {
            static void Log(string msg)
            {
                Debug.Log(msg);
            }

            PCGEngine.SetLoggingFunction(Log);

            float nodeSize = nodeSizeField.value;
            Vector2Int gridSize = gridSizeField.value;

            if (mazeNode == null)
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

            Transform nodeParent = new GameObject("Maze").transform;

            if (frameByFrameToggle.value)
            {
                List<NodeInfo> nodes = new List<NodeInfo>();

                void AddNodeInfo(int x, int y, MazeDirection adjacentNodes)
                {
                    nodes.Add(new NodeInfo()
                    {
                        x = x,
                        y = y,
                        adjacentNodes = adjacentNodes,
                        size = nodeSize
                    });
                }

                PCGEngine.GenerateMaze(gridSize.x, gridSize.y, delayedInvoke.value, (MazeAlgorithm)mazeAlgorithmField.value, AddNodeInfo);

                if (delayedInvoke.value)
                {
                    EditorCoroutineUtility.StartCoroutine(DelayedGeneration(nodes, nodeParent), this);
                }
                else
                {
                    EditorCoroutineUtility.StartCoroutine(Generation(nodes, nodeParent), this);
                }
            }
            else
            {
                void AddMazeNode(int x, int y, MazeDirection adjacentNodes)
                {
                    AddNode(nodeParent, new NodeInfo { x = x, y = y, adjacentNodes = adjacentNodes, size = nodeSize });
                }

                PCGEngine.GenerateMaze(gridSize.x, gridSize.y, true, (MazeAlgorithm)mazeAlgorithmField.value, AddMazeNode);
            }
        }

        /// <summary>
        /// Spawn node in world
        /// </summary>
        /// <param name="nodeParent">Node parent</param>
        /// <param name="nodeInfo">Node info in grid</param>
        /// <returns>Spawned node</returns>
        private IMazeNode AddNode(Transform nodeParent, NodeInfo nodeInfo)
        {
            UnityEngine.Vector3 position = new UnityEngine.Vector3(nodeInfo.x * nodeInfo.size, 0, nodeInfo.y * nodeInfo.size);
            IMazeNode node = Instantiate(mazeNode.gameObject, nodeParent).GetComponent<IMazeNode>();
            node.transform.localPosition = position;
            node.SetAdjacentNodes(nodeInfo.adjacentNodes);
            return node;
        }

        /// <summary>
        /// Spawn maze all generation is completed
        /// </summary>
        /// <param name="nodes">List of nodes in maze</param>
        /// <param name="nodeParent">Node parent</param>
        private IEnumerator DelayedGeneration(List<NodeInfo> nodes, Transform nodeParent)
        {
            foreach (NodeInfo node in nodes)
            {
                if (nodeParent == null)
                {
                    Debug.LogError("Maze Parent has been deleted generation stopping");
                    yield break;
                }

                AddNode(nodeParent, node);
                yield return null;
            }
        }

        /// <summary>
        /// Spawn maze while generation is still running
        /// </summary>
        /// <param name="nodes">List of nodes in maze</param>
        /// <param name="nodeParent">Node parent</param>
        private IEnumerator Generation(List<NodeInfo> nodes, Transform nodeParent)
        {
            Dictionary<Vector2, IMazeNode> spawnedNodes = new Dictionary<Vector2, IMazeNode>();

            foreach (NodeInfo nodeInfo in nodes)
            {
                if (nodeParent == null)
                {
                    Debug.LogError("Maze Parent has been deleted generation stopping");
                    yield break;
                }

                Vector2 key = new Vector2(nodeInfo.x, nodeInfo.y);

                if (spawnedNodes.ContainsKey(key))
                {
                    spawnedNodes[key].SetAdjacentNodes(nodeInfo.adjacentNodes);
                }
                else
                {
                    IMazeNode node = AddNode(nodeParent, nodeInfo);
                    spawnedNodes.Add(key, node);
                }

                yield return null;
            }
        }
    }
}
