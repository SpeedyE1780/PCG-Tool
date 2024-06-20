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
        private DropdownField mazeAlgorithmField;

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
            mazeAlgorithmField = rootVisualElement.Q<DropdownField>("MazeAlgorithm");

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

            WFCNode node = nodeField.value as WFCNode;
            float size = nodeSizeField.value;
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

            if (size == 0)
            {
                Debug.LogWarning("Node size not set");
                return;
            }

            PCGEngine.SetSeed(seedField.value);

            Transform nodeParent = new GameObject("MAZE").transform;

            void AddMazeNode(int x, int y, Direction adjacentNodes)
            {
                UnityEngine.Vector3 position = new UnityEngine.Vector3(x * size, 0, y * size);
                WFCNode n = Instantiate(node, nodeParent);
                n.transform.position = position;
                n.SetNeighbors(adjacentNodes);
            }

            PCGEngine.GenerateMaze(gridSize.x, gridSize.y, true, (MazeAlgorithm)mazeAlgorithmField.index, AddMazeNode);
        }
    }
}
