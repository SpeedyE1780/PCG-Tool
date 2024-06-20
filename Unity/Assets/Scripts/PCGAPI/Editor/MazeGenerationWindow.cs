using PCGAPI;
using PCGAPI.Generators;
using System.Collections.Generic;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

public class MazeGenerationWindow : EditorWindow
{
    [SerializeField]
    private VisualTreeAsset m_VisualTreeAsset = default;

    private ObjectField nodeField;
    private Vector2IntField gridSizeField;
    private FloatField nodeSize;
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
        nodeSize = rootVisualElement.Q<FloatField>("NodeSize");
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

        //PCGEngine.SetLoggingFunction(Log);

        WFCNode node = nodeField.value as WFCNode;
        float size = nodeSize.value;
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

        Dictionary<Vector2, WFCNode> nodes = new Dictionary<Vector2, WFCNode>();
        Transform nodeParent = new GameObject("MAZE").transform;

        void AddMazeNode(int x, int y, Direction neighbors)
        {
            if (!nodes.ContainsKey(new Vector2(x, y)))
            {
                UnityEngine.Vector3 position = new UnityEngine.Vector3(x * size, 0, y * size);
                WFCNode n = Instantiate(node, nodeParent);
                n.transform.position = position;
                n.SetNeighbors(neighbors);
                nodes.Add(new Vector2(x, y), n);
            }
            else
            {
                nodes[new Vector2(x, y)].SetNeighbors(neighbors);
            }
        }

        PCGEngine.GenerateMaze(gridSize.x, gridSize.y, false, (MazeAlgorithm)mazeAlgorithmField.index, AddMazeNode);
    }
}
