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
        XY = Axis.xy,
        XZ = Axis.xz,
        YZ = Axis.yz,
    }

    private struct Node2DInfo
    {
        public int x;
        public int y;
        public float size;
        public LevelGenerationDirection adjacentNodes;
    }

    private struct Node3DInfo
    {
        public int x;
        public int y;
        public int z;
        public float size;
        public LevelGenerationDirection adjacentNodes;
    }

    private delegate UnityEngine.Vector3 Place2DNode(int x, int y, float size);

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

    private IWFCNode wfcNode;

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

        nodeField.RegisterValueChangedCallback(ValidateNodeField);
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
        float size = nodeSizeField.value;
        Vector2Int gridSize = grid2DSizeField.value;
        Place2DNode placingFunction = GetPositioningDelegate();

        if (wfcNode == null)
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

            void AddNodeInfo(int x, int y, LevelGenerationDirection adjacentNodes)
            {
                nodes.Add(new Node2DInfo()
                {
                    x = x,
                    y = y,
                    size = size,
                    adjacentNodes = adjacentNodes
                });
            }

            PCGEngine.WaveFunctionCollapseGeneration(gridSize.x, gridSize.y, (Axis)grid2DPlane.value, true, AddNodeInfo);
            EditorCoroutineUtility.StartCoroutine(Spawn2DGrid(nodes, wfcNode, nodeParent, placingFunction), this);
        }
        else
        {
            void AddGridNode(int x, int y, LevelGenerationDirection adjacentNodes)
            {
                AddNode(wfcNode, nodeParent, placingFunction, size, x, y, adjacentNodes);
            }

            PCGEngine.WaveFunctionCollapseGeneration(gridSize.x, gridSize.y, (Axis)grid2DPlane.value, true, AddGridNode);
        }
    }

    void AddNode(IWFCNode node, Transform nodeParent, Place2DNode placingFunction, float nodeSize, int x, int y, LevelGenerationDirection adjacentNodes)
    {
        if (adjacentNodes != LevelGenerationDirection.none)
        {
            UnityEngine.Vector3 position = placingFunction(x, y, nodeSize);
            IWFCNode n = Instantiate(node.gameObject, nodeParent).GetComponent<IWFCNode>();
            n.transform.position = position;
            n.SetAdjacentNodes(adjacentNodes);
        }
    }

    private IEnumerator Spawn2DGrid(List<Node2DInfo> nodes, IWFCNode node, Transform nodeParent, Place2DNode placingFunction)
    {
        foreach (Node2DInfo nodeInfo in nodes)
        {
            if (nodeParent == null)
            {
                Debug.LogError("Grid Parent has been deleted generation stopping");
                yield break;
            }

            AddNode(node, nodeParent, placingFunction, nodeInfo.size, nodeInfo.x, nodeInfo.y, nodeInfo.adjacentNodes);
            yield return null;
        }
    }

    private void Spawn3DGrid()
    {
        float size = nodeSizeField.value;
        Vector3Int gridSize = grid3DSizeField.value;

        if (wfcNode == null)
        {
            Debug.LogWarning("Node not set");
            return;
        }

        if (size == 0)
        {
            Debug.LogWarning("Node size not set");
            return;
        }

        Transform nodeParent = new GameObject("Grid 3D WFC Generation").transform;

        if (frameByFrameToggle.value)
        {
            List<Node3DInfo> nodes = new List<Node3DInfo>();

            void AddNodeInfo(int x, int y, int z, LevelGenerationDirection adjacentNodes)
            {
                nodes.Add(new Node3DInfo()
                {
                    x = x,
                    y = y,
                    z = z,
                    size = size,
                    adjacentNodes = adjacentNodes
                });
            }

            PCGEngine.WaveFunctionCollapseGeneration(gridSize.x, gridSize.y, gridSize.z, true, AddNodeInfo);
            EditorCoroutineUtility.StartCoroutine(Spawn3DGrid(nodes, wfcNode, nodeParent), this);
        }
        else
        {
            void AddGridNode(int x, int y, int z, LevelGenerationDirection adjacentNodes)
            {
                AddNode(wfcNode, nodeParent, size, x, y, z, adjacentNodes);
            }

            PCGEngine.WaveFunctionCollapseGeneration(gridSize.x, gridSize.y, gridSize.z, true, AddGridNode);
        }
    }

    void AddNode(IWFCNode node, Transform nodeParent, float size, int x, int y, int z, LevelGenerationDirection adjacentNodes)
    {
        if (adjacentNodes != LevelGenerationDirection.none)
        {
            UnityEngine.Vector3 position = new UnityEngine.Vector3(x * nodeSizeField.value, nodeSizeField.value * y, nodeSizeField.value * z);
            IWFCNode n = Instantiate(node.gameObject, nodeParent).GetComponent<IWFCNode>();
            n.transform.position = position;
            n.SetAdjacentNodes(adjacentNodes);
        }
    }

    private IEnumerator Spawn3DGrid(List<Node3DInfo> nodes, IWFCNode node, Transform nodeParent)
    {
        foreach (Node3DInfo nodeInfo in nodes)
        {
            if (nodeParent == null)
            {
                Debug.LogError("Grid Parent has been deleted generation stopping");
                yield break;
            }

            AddNode(node, nodeParent, nodeInfo.size, nodeInfo.x, nodeInfo.y, nodeInfo.z, nodeInfo.adjacentNodes);
            yield return null;
        }
    }
}
