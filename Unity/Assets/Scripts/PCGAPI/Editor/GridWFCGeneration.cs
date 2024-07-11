using PCGAPI;
using System.Collections;
using System.Collections.Generic;
using Unity.EditorCoroutines.Editor;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

public class GridWFCGeneration : EditorWindow
{
    private enum Plane
    {
        XY,
        XZ,
        YZ
    }

    private struct Node2DInfo
    {
        public int x;
        public int y;
        public float size;
        public Direction adjacentNodes;
    }

    private delegate UnityEngine.Vector3 Place2DNode(int x, int y, float  size);

    [SerializeField]
    private VisualTreeAsset m_VisualTreeAsset = default;

    private ObjectField nodeField;
    private FloatField nodeSizeField;
    private UnsignedIntegerField seedField;
    private DropdownField gridDimensionField;
    private EnumField grid2DPlane;
    private Toggle frameByFrameToggle;
    private Vector2IntField grid2DSizeField;
    private Vector3IntField grid3DSizeField;
    private VisualElement grid2DContainer;
    private VisualElement grid3DContainer;
    private bool grid3DGeneration = false;

    [MenuItem("PCG/Grid Wave Function Collapse Generation")]
    public static void ShowExample()
    {
        GridWFCGeneration wnd = GetWindow<GridWFCGeneration>();
        wnd.titleContent = new GUIContent("Grid Wave Function Collapse Generation");
    }

    private void OnDimensionChange()
    {
        grid2DContainer.style.display = gridDimensionField.value == "2D Grid" ? DisplayStyle.Flex : DisplayStyle.None;
        grid3DContainer.style.display = gridDimensionField.value == "3D Grid" ? DisplayStyle.Flex : DisplayStyle.None;
        grid3DGeneration = gridDimensionField.value == "3D Grid";
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
        grid2DPlane = rootVisualElement.Q<EnumField>("2DPlane");
        grid3DSizeField = rootVisualElement.Q<Vector3IntField>("Grid3DSize");
        grid2DContainer = rootVisualElement.Q<VisualElement>("Grid2D");
        grid3DContainer = rootVisualElement.Q<VisualElement>("Grid3D");

        gridDimensionField.RegisterValueChangedCallback((eventChange) => OnDimensionChange());
        OnDimensionChange();

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
        PCGEngine.SetSeed(seedField.value);
        if (grid3DGeneration)
        {
            Spawn3DGrid();
        }
        else
        {
            Spawn2DGrid(); 
        }
    }

    private Place2DNode GetPositioningDelegate()
    {
        switch ((Plane)grid2DPlane.value)
        {
            case Plane.XY:
                {
                    return (int x, int y, float size) => { return new UnityEngine.Vector3(x * size, y * size, 0); };
                }
            case Plane.XZ:
                {
                    return (int x, int y, float size) => { return new UnityEngine.Vector3(x * size, 0, y * size); };
                }
            case Plane.YZ:
                {
                    return (int x, int y, float size) => { return new UnityEngine.Vector3(0, x * size, y * size); };
                }
            default:
                {
                    return null;
                }
        }
    }

    private void Spawn2DGrid()
    {
        WFCNode node = nodeField.value as WFCNode;
        float size = nodeSizeField.value;
        Vector2Int gridSize = grid2DSizeField.value;
        Place2DNode placingFunction = GetPositioningDelegate();

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

        Transform nodeParent = new GameObject("Grid 2D WFC Generation").transform;

        if (frameByFrameToggle.value)
        {
            List<Node2DInfo> nodes = new List<Node2DInfo>();
            
            void AddNodeInfo(int x, int y, Direction adjacentNodes)
            {
                nodes.Add(new Node2DInfo()
                {
                    x = x,
                    y = y,
                    size = size,
                    adjacentNodes = adjacentNodes
                });
            }

            PCGEngine.WaveFunctionCollapseGeneration(gridSize.x, gridSize.y, true, AddNodeInfo);
            EditorCoroutineUtility.StartCoroutine(Spawn2DGrid(nodes, node, nodeParent, placingFunction), this);
        }
        else
        {
            void AddGridNode(int x, int y, Direction adjacentNodes)
            {
                AddNode(node, nodeParent, placingFunction, size, x, y, adjacentNodes);
            }

            PCGEngine.WaveFunctionCollapseGeneration(gridSize.x, gridSize.y, true, AddGridNode);
        }
    }

    void AddNode(WFCNode node, Transform nodeParent, Place2DNode placingFunction, float nodeSize, int x, int y, Direction adjacentNodes)
    {
        if (adjacentNodes != Direction.none)
        {
            UnityEngine.Vector3 position = placingFunction(x, y, nodeSize);
            WFCNode n = Instantiate(node, nodeParent);
            n.transform.position = position;
            n.SetNeighbors(adjacentNodes);
        }
    }

    private IEnumerator Spawn2DGrid(List<Node2DInfo> nodes, WFCNode node, Transform nodeParent,Place2DNode placingFunction)
    {
        foreach (Node2DInfo nodeInfo in nodes)
        {
            AddNode(node, nodeParent, placingFunction, nodeInfo.size, nodeInfo.x, nodeInfo.y, nodeInfo.adjacentNodes);
            yield return null;
        }
    }

    private void Spawn3DGrid()
    {

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
