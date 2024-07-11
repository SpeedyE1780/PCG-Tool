using PCGAPI;
using System.Collections.Generic;
using Unity.EditorCoroutines.Editor;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

public class GridWFCGeneration : EditorWindow
{
    [SerializeField]
    private VisualTreeAsset m_VisualTreeAsset = default;

    private ObjectField nodeField;
    private FloatField nodeSizeField;
    private UnsignedIntegerField seedField;
    private DropdownField gridDimensionField;
    private Toggle frameByFrameToggle;
    private Vector2IntField grid2DSizeField;

    [MenuItem("PCG/Grid Wave Function Collapse Generation")]
    public static void ShowExample()
    {
        GridWFCGeneration wnd = GetWindow<GridWFCGeneration>();
        wnd.titleContent = new GUIContent("Grid Wave Function Collapse Generation");
    }

    public void CreateGUI()
    {
        // Instantiate UXML
        VisualElement uxmlElements = m_VisualTreeAsset.Instantiate();
        rootVisualElement.Add(uxmlElements);
        nodeField = rootVisualElement.Q<ObjectField>("Node");
        nodeSizeField = rootVisualElement.Q<FloatField>("NodeSize");
        seedField = rootVisualElement.Q<UnsignedIntegerField>("Seed");
        frameByFrameToggle = rootVisualElement.Q<Toggle>("FramebyFrame");
        gridDimensionField = rootVisualElement.Q<DropdownField>("GridDimension");
        grid2DSizeField = rootVisualElement.Q<Vector2IntField>("Grid2DSize");

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

        if (node == null)
        {
            Debug.LogWarning("Node not set");
            return;
        }

        if (size == 0)
        {
            Debug.LogWarning("Node size not set");
            return;
        }

        PCGEngine.SetSeed(seedField.value);
        Transform nodeParent = new GameObject("Grid WFC Generation").transform;
        if (frameByFrameToggle.value)
        {
            //EditorCoroutineUtility.StartCoroutine(SpawnLevel(nodes), this);
        }
        else
        {
            void AddGridNode(int x, int y, Direction adjacentNodes)
            {
                AddNode(nodeParent, node, x, y, adjacentNodes);
            }

            PCGEngine.WaveFunctionCollapseGeneration(5, 5, true, AddGridNode);
        }
    }

    void AddNode(Transform nodeParent, WFCNode node, int x, int y, Direction adjacentNodes)
    {
        if (adjacentNodes != Direction.none)
        {
            UnityEngine.Vector3 position = new UnityEngine.Vector3(x * nodeSizeField.value, 0, nodeSizeField.value * y);
            WFCNode n = Instantiate(node, nodeParent);
            n.transform.position = position;
            n.SetNeighbors(adjacentNodes);
        }
    }

    //void AddNode(int x, int y, int z, Direction adjacentNodes)
    //{
    //    if (adjacentNodes != Direction.none)
    //    {
    //        UnityEngine.Vector3 position = new UnityEngine.Vector3(x * nodeSizeField.value, nodeSizeField.value * y, nodeSizeField.value * z);
    //        WFCNode n = Instantiate(node, nodeParent);
    //        n.transform.position = position;
    //        n.SetNeighbors(adjacentNodes);
    //    }
    //}
}
