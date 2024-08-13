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
    /// Class used to create grid level with wave function collapse generation
    /// </summary>
    public class GridWFCGeneration : EditorWindow
    {
        /// <summary>
        /// Plane used to generate 2D grid level
        /// </summary>
        private enum Plane
        {
            XY = Axis.xy,
            XZ = Axis.xz,
            YZ = Axis.yz,
        }

        /// <summary>
        /// Contains all info related to a node in 2D grid
        /// </summary>
        private struct Node2DInfo
        {
            public int x;
            public int y;
            public float size;
            public LevelGenerationDirection adjacentNodes;
        }

        /// <summary>
        /// Contains all info related to a node in 3D grid
        /// </summary>
        private struct Node3DInfo
        {
            public int x;
            public int y;
            public int z;
            public float size;
            public LevelGenerationDirection adjacentNodes;
        }

        /// <summary>
        /// Function used to convert 2D grid coordinates to world position
        /// </summary>
        /// <param name="x">X coordinate</param>
        /// <param name="y">Y coordinate</param>
        /// <param name="size">Node size</param>
        /// <returns>Node world position</returns>
        private delegate UnityEngine.Vector3 Place2DNode(int x, int y, float size);

        [SerializeField, Tooltip("Grid Generation Window UXML File")]
        private VisualTreeAsset windowUXML = default;

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

        /// <summary>
        /// Adds menu item to Unity Editor to open window
        /// </summary>
        [MenuItem("PCG/Grid Wave Function Collapse Generation")]
        public static void OpenWindow()
        {
            GridWFCGeneration wnd = GetWindow<GridWFCGeneration>();
            wnd.titleContent = new GUIContent("Grid Wave Function Collapse Generation");
        }

        /// <summary>
        /// Hide unrelated 2D/3D fields when dimension is changed
        /// </summary>
        private void OnDimensionChange(string dimension)
        {
            grid2DContainer.style.display = dimension == "2D Grid" ? DisplayStyle.Flex : DisplayStyle.None;
            grid3DContainer.style.display = dimension == "3D Grid" ? DisplayStyle.Flex : DisplayStyle.None;
            grid3DGeneration = dimension == "3D Grid";
        }

        /// <summary>
        /// Called when window is created
        /// </summary>
        public void CreateGUI()
        {
            VisualElement gridWindow = windowUXML.Instantiate();
            rootVisualElement.Add(gridWindow);
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

            gridDimensionField.RegisterValueChangedCallback((eventChange) => OnDimensionChange(eventChange.newValue));
            OnDimensionChange(gridDimensionField.value);

            var generateButton = rootVisualElement.Q<Button>("GenerateButton");
            generateButton.clicked += GenerateGrid;

            nodeField.RegisterValueChangedCallback((changeEvent) => WindowHelper.ValidateGameObjectField(ref wfcNode, nodeField, changeEvent));
        }

        /// <summary>
        /// Generate grid using wave function collapse
        /// </summary>
        private void GenerateGrid()
        {
            static void Log(string msg)
            {
                Debug.Log(msg);
            }

            PCGEngine.SetLoggingFunction(Log);
            PCGEngine.SetSeed(seedField.value);

            float size = nodeSizeField.value;

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

            if (grid3DGeneration)
            {
                Spawn3DGrid(size);
            }
            else
            {
                Spawn2DGrid(size);
            }
        }

        /// <summary>
        /// Get function to convert 2D coordinates to 3D world position
        /// </summary>
        /// <param name="gridPlane">2D grid plane</param>
        /// <returns>Function to convert 2D coordinates to 3D world position</returns>
        private Place2DNode GetPositioningDelegate(Plane gridPlane)
        {
            switch (gridPlane)
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

        /// <summary>
        /// Generate 2D grid using wave function collapse
        /// </summary>
        /// <param name="size">Node size</param>
        private void Spawn2DGrid(float size)
        {
            Vector2Int gridSize = grid2DSizeField.value;
            Place2DNode placingFunction = GetPositioningDelegate((Plane)grid2DPlane.value);

            if (gridSize.x <= 0 || gridSize.y <= 0)
            {
                Debug.LogWarning("Grid size is not valid");
                return;
            }

            Transform nodeParent = new GameObject("Grid 2D WFC Generation").transform;

            if (frameByFrameToggle.value)
            {
                List<Node2DInfo> nodes = new List<Node2DInfo>();

                void AddNodeInfo(int x, int y, LevelGenerationDirection adjacentNodes)
                {
                    //Skip nodes with no adjacent nodes
                    if (adjacentNodes != LevelGenerationDirection.none)
                    {
                        nodes.Add(new Node2DInfo()
                        {
                            x = x,
                            y = y,
                            size = size,
                            adjacentNodes = adjacentNodes
                        });
                    }
                }

                PCGEngine.WaveFunctionCollapseGeneration(gridSize.x, gridSize.y, (Axis)grid2DPlane.value, true, AddNodeInfo);
                EditorCoroutineUtility.StartCoroutine(Spawn2DGrid(nodes, wfcNode, nodeParent, placingFunction), this);
            }
            else
            {
                void AddGridNode(int x, int y, LevelGenerationDirection adjacentNodes)
                {
                    //Skip nodes with no adjacent nodes
                    if (adjacentNodes != LevelGenerationDirection.none)
                    {
                        AddNode(wfcNode, nodeParent, placingFunction, size, x, y, adjacentNodes);
                    }
                }

                PCGEngine.WaveFunctionCollapseGeneration(gridSize.x, gridSize.y, (Axis)grid2DPlane.value, true, AddGridNode);
            }
        }

        /// <summary>
        /// Spawn node in grid
        /// </summary>
        /// <param name="node">Node prefab</param>
        /// <param name="nodeParent">Node parent</param>
        /// <param name="placingFunction">Function used to convert 2D coordinates to 3D world position</param>
        /// <param name="nodeSize">Node size</param>
        /// <param name="x">X coordinate</param>
        /// <param name="y">Y coordinate</param>
        /// <param name="adjacentNodes">Adjacent nodes bit mask</param>
        void AddNode(IWFCNode node, Transform nodeParent, Place2DNode placingFunction, float nodeSize, int x, int y, LevelGenerationDirection adjacentNodes)
        {
            UnityEngine.Vector3 position = placingFunction(x, y, nodeSize);
            IWFCNode n = Instantiate(node.gameObject, nodeParent).GetComponent<IWFCNode>();
            n.transform.position = position;
            n.SetAdjacentNodes(adjacentNodes);
        }

        /// <summary>
        /// Spawn grid frame by frame
        /// </summary>
        /// <param name="nodes">List of nodes to spawn</param>
        /// <param name="node">Node prefab</param>
        /// <param name="nodeParent">Node parent</param>
        /// <param name="placingFunction">Function used to convert 2D coordinates to 3D world position</param>
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

        /// <summary>
        /// Generate 3D grid using wave function collapse
        /// </summary>
        /// <param name="size">Node size</param>
        private void Spawn3DGrid(float size)
        {
            Vector3Int gridSize = grid3DSizeField.value;

            if (gridSize.x <= 0 || gridSize.y <= 0 || gridSize.z <= 0)
            {
                Debug.LogWarning("Grid size is not valid");
                return;
            }

            Transform nodeParent = new GameObject("Grid 3D WFC Generation").transform;

            if (frameByFrameToggle.value)
            {
                List<Node3DInfo> nodes = new List<Node3DInfo>();

                void AddNodeInfo(int x, int y, int z, LevelGenerationDirection adjacentNodes)
                {
                    if (adjacentNodes != LevelGenerationDirection.none)
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
                }

                PCGEngine.WaveFunctionCollapseGeneration(gridSize.x, gridSize.y, gridSize.z, true, AddNodeInfo);
                EditorCoroutineUtility.StartCoroutine(Spawn3DGrid(nodes, wfcNode, nodeParent), this);
            }
            else
            {
                void AddGridNode(int x, int y, int z, LevelGenerationDirection adjacentNodes)
                {
                    //Skip nodes with no adjacent nodes
                    if (adjacentNodes != LevelGenerationDirection.none)
                    {
                        AddNode(wfcNode, nodeParent, size, x, y, z, adjacentNodes);
                    }
                }

                PCGEngine.WaveFunctionCollapseGeneration(gridSize.x, gridSize.y, gridSize.z, true, AddGridNode);
            }
        }

        /// <summary>
        /// Spawn node in grid
        /// </summary>
        /// <param name="node">Node prefab</param>
        /// <param name="nodeParent">Node parent</param>
        /// <param name="size">Node size</param>
        /// <param name="x">X coordinate</param>
        /// <param name="y">Y coordinate</param>
        /// <param name="z">Z coordinate</param>
        /// <param name="adjacentNodes">Adjacent nodes bit mask</param>
        void AddNode(IWFCNode node, Transform nodeParent, float size, int x, int y, int z, LevelGenerationDirection adjacentNodes)
        {
            UnityEngine.Vector3 position = new UnityEngine.Vector3(x * nodeSizeField.value, nodeSizeField.value * y, nodeSizeField.value * z);
            IWFCNode n = Instantiate(node.gameObject, nodeParent).GetComponent<IWFCNode>();
            n.transform.position = position;
            n.SetAdjacentNodes(adjacentNodes);
        }

        /// <summary>
        /// Spawn grid frame by frame
        /// </summary>
        /// <param name="nodes">List of nodes to spawn</param>
        /// <param name="node">Node prefab</param>
        /// <param name="nodeParent">Node parent</param>
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
}
