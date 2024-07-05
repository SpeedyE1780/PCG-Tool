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
        private IMazeNode mazeNode;

        struct NodeInfo
        {
            public int x;
            public int y;
            public float size;
            public Direction adjacentNodes;
        }

        [MenuItem("PCG/Maze Generation")]
        public static void OpenMazeWindow()
        {
            MazeGenerationWindow wnd = GetWindow<MazeGenerationWindow>();
            wnd.titleContent = new GUIContent("Maze Generation");
        }

        private void ValidateNodeField(ChangeEvent<Object> changeEvent)
        {
            if (changeEvent.newValue == null)
            {
                return;
            }

            GameObject newGameObject = changeEvent.newValue as GameObject;

            if (newGameObject != null && newGameObject.TryGetComponent(out mazeNode))
            {
                return;
            }

            Debug.LogError($"{newGameObject.name} has no component that inherits from IMazeNode");
            nodeField.value = changeEvent.previousValue; //this will call the event again
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

            nodeField.RegisterValueChangedCallback(ValidateNodeField);
        }

        private void SpawnObject()
        {
            static void Log(string msg)
            {
                Debug.Log(msg);
            }

            PCGEngine.SetLoggingFunction(Log);

            float nodeSize = nodeSizeField.value;
            Vector2Int gridSize = gridSizeField.value;

            if (nodeField.value == null)
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

            Transform nodeParent = new GameObject("MAZE").transform;

            if (frameByFrameToggle.value)
            {
                List<NodeInfo> nodes = new List<NodeInfo>();

                void AddNodeInfo(int x, int y, Direction adjacentNodes)
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
                void AddMazeNode(int x, int y, Direction adjacentNodes)
                {
                    AddNode(nodeParent, new NodeInfo { x = x, y = y, adjacentNodes = adjacentNodes, size = nodeSize });
                }

                PCGEngine.GenerateMaze(gridSize.x, gridSize.y, true, (MazeAlgorithm)mazeAlgorithmField.value, AddMazeNode);
            }
        }

        private IMazeNode AddNode(Transform nodeParent, NodeInfo nodeInfo)
        {
            UnityEngine.Vector3 position = new UnityEngine.Vector3(nodeInfo.x * nodeInfo.size, 0, nodeInfo.y * nodeInfo.size);
            IMazeNode node = Instantiate(mazeNode.gameObject, nodeParent).GetComponent<IMazeNode>();
            node.transform.position = position;
            node.SetAdjacentNodes(nodeInfo.adjacentNodes);
            return node;
        }

        private IEnumerator DelayedGeneration(List<NodeInfo> nodes, Transform nodeParent)
        {
            foreach (NodeInfo node in nodes)
            {
                AddNode(nodeParent, node);
                yield return null;
            }
        }

        private IEnumerator Generation(List<NodeInfo> nodes, Transform nodeParent)
        {
            Dictionary<Vector2, IMazeNode> spawnedNodes = new Dictionary<Vector2, IMazeNode>();

            foreach (NodeInfo nodeInfo in nodes)
            {
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
