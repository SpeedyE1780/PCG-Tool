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
    /// Class used to create level on multiple axes
    /// </summary>
    public class MultiDimensionalGeneration : EditorWindow
    {
        [SerializeField, Tooltip("Multi Dimension Generation Window UXML File")]
        private VisualTreeAsset windowUXML = default;

        private ObjectField nodeField;
        private UnsignedIntegerField nodeCountField;
        private FloatField nodeSizeField;
        private UnsignedIntegerField seedField;
        private EnumFlagsField axesField;
        private Toggle disableOverlapToggle;
        private Vector3Field startPosition;
        private Toggle frameByFrameToggle;

        /// <summary>
        /// Adds menu item to Unity Editor to open window
        /// </summary>
        [MenuItem("PCG/Multi Dimensional Generation")]
        public static void OpenWindow()
        {
            MultiDimensionalGeneration wnd = GetWindow<MultiDimensionalGeneration>();
            wnd.titleContent = new GUIContent("Multi Dimensional Generation");
        }

        /// <summary>
        /// Called when window is created
        /// </summary>
        public void CreateGUI()
        {
            VisualElement uxmlElements = windowUXML.Instantiate();
            rootVisualElement.Add(uxmlElements);

            nodeField = rootVisualElement.Q<ObjectField>("Node");
            nodeCountField = rootVisualElement.Q<UnsignedIntegerField>("Count");
            nodeSizeField = rootVisualElement.Q<FloatField>("Size");
            seedField = rootVisualElement.Q<UnsignedIntegerField>("Seed");
            disableOverlapToggle = rootVisualElement.Q<Toggle>("DisableOverlap");
            startPosition = rootVisualElement.Q<Vector3Field>("StartPosition");
            axesField = rootVisualElement.Q<EnumFlagsField>("Axes");
            frameByFrameToggle = rootVisualElement.Q<Toggle>("FrameByFrame");

            var generateButton = rootVisualElement.Q<Button>("GenerateButton");
            generateButton.clicked += GenerateLevel;
        }

        /// <summary>
        /// Generate level on selected axes
        /// </summary>
        private void GenerateLevel()
        {
            static void Log(string msg)
            {
                Debug.Log(msg);
            }

            PCGEngine.SetLoggingFunction(Log);

            GameObject node = nodeField.value as GameObject;
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

            Transform nodeParent = new GameObject("Multi Dimensional Generation").transform;

            GenerationParameters generationParameters = new GenerationParameters()
            {
                count = nodeCount,
                size = size,
                startPoint = PCGEngine2Unity.UnityToPCGEngineVector(startPosition.value)
            };

            if (frameByFrameToggle.value)
            {
                List<Vector3> positions = new List<Vector3>();

                void AddNodePosition(Vector3 nodePosition)
                {
                    positions.Add(nodePosition);
                }

                PCGEngine.MultiDimensionalGeneration(ref generationParameters, (Axis)axesField.value, disableOverlapToggle.value, AddNodePosition);
                EditorCoroutineUtility.StartCoroutine(GenerateLevel(node, nodeParent, positions), this);
            }
            else
            {
                void SpawnNode(Vector3 nodePosition)
                {
                    AddNode(node, nodeParent, nodePosition);
                }

                PCGEngine.MultiDimensionalGeneration(ref generationParameters, (Axis)axesField.value, disableOverlapToggle.value, SpawnNode);
            }

        }

        /// <summary>
        /// Spawn node in scene
        /// </summary>
        /// <param name="node">Node prefab</param>
        /// <param name="parent">Node parent</param>
        /// <param name="nodePosition">Node world position</param>
        private void AddNode(GameObject node, Transform parent, Vector3 nodePosition)
        {
            UnityEngine.Vector3 position = PCGEngine2Unity.PCGEngineVectorToUnity(nodePosition);
            GameObject n = Instantiate(node, parent);
            n.transform.position = position;
        }

        /// <summary>
        /// Spawn nodes frame by frame
        /// </summary>
        /// <param name="node">Node prefab</param>
        /// <param name="nodeParent">Node parent</param>
        /// <param name="positions">Node world position</param>
        private IEnumerator GenerateLevel(GameObject node, Transform nodeParent, List<Vector3> positions)
        {
            foreach (Vector3 position in positions)
            {
                if (nodeParent == null)
                {
                    Debug.LogError("Node parent was destroyed ending generation early");
                    yield break;
                }

                AddNode(node, nodeParent, position);
                yield return null;
            }
        }
    }
}
