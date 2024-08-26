using System.Collections.Generic;
using Unity.EditorCoroutines.Editor;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    /// <summary>
    /// Class used to generate levels on a single axis
    /// </summary>
    public class SimpleGeneration : EditorWindow
    {
        [SerializeField, Tooltip("Simple Generation Window UXML File")]
        private VisualTreeAsset windowUXML = default;

        private ObjectField nodeField;
        private UnsignedIntegerField nodeCountField;
        private FloatField nodeSizeField;
        private Vector3Field startPosition;
        private Vector3Field offset;
        private Toggle frameByFrameToggle;

        /// <summary>
        /// Adds menu item to Unity Editor to open window
        /// </summary>
        [MenuItem("PCG/Simple Generation")]
        public static void OpenWindow()
        {
            SimpleGeneration wnd = GetWindow<SimpleGeneration>();
            wnd.titleContent = new GUIContent("Simple Generation");
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
            offset = rootVisualElement.Q<Vector3Field>("NodeOffset");
            startPosition = rootVisualElement.Q<Vector3Field>("StartPosition");
            frameByFrameToggle = rootVisualElement.Q<Toggle>("FramebyFrame");

            var generateButton = rootVisualElement.Q<Button>("GenerateButton");
            generateButton.clicked += GenerateLevel;
        }

        /// <summary>
        /// Spawns selected gameobject along chosen axis
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

            Transform nodeParent = new GameObject("Simple Generation").transform;

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

                PCGEngine.SimpleGeneration(generationParameters, PCGEngine2Unity.UnityToPCGEngineVector(offset.value), AddNodePosition);
                EditorCoroutineUtility.StartCoroutine(WindowHelper.GenerateLevel(node, nodeParent, positions), this);
            }
            else
            {
                void SpawnNode(Vector3 nodePosition)
                {
                    WindowHelper.SpawnNode(node, nodeParent, nodePosition);
                }

                PCGEngine.SimpleGeneration(generationParameters, PCGEngine2Unity.UnityToPCGEngineVector(offset.value), SpawnNode);
            }
        }
    }
}
