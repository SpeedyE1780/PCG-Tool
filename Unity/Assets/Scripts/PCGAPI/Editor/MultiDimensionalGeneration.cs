using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    public class MultiDimensionalGeneration : EditorWindow
    {
        [SerializeField]
        private VisualTreeAsset m_VisualTreeAsset = default;

        private ObjectField nodeField;
        private UnsignedIntegerField nodeCountField;
        private FloatField nodeSizeField;
        private UnsignedIntegerField seedField;
        private EnumFlagsField axesField;
        private Toggle disableOverlapToggle;
        private Vector3Field startPosition;

        [MenuItem("PCG/Multi Dimensional Generation")]
        public static void ShowExample()
        {
            MultiDimensionalGeneration wnd = GetWindow<MultiDimensionalGeneration>();
            wnd.titleContent = new GUIContent("Multi Dimensional Generation");
        }

        public void CreateGUI()
        {
            // Instantiate UXML
            VisualElement uxmlElements = m_VisualTreeAsset.Instantiate();
            rootVisualElement.Add(uxmlElements);

            nodeField = rootVisualElement.Q<ObjectField>("Node");
            nodeCountField = rootVisualElement.Q<UnsignedIntegerField>("Count");
            nodeSizeField = rootVisualElement.Q<FloatField>("Size");
            seedField = rootVisualElement.Q<UnsignedIntegerField>("Seed");
            disableOverlapToggle = rootVisualElement.Q<Toggle>("DisableOverlap");
            startPosition = rootVisualElement.Q<Vector3Field>("StartPosition");
            axesField = rootVisualElement.Q<EnumFlagsField>("Axes");

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

            void AddNode(Vector3 nodePosition)
            {
                UnityEngine.Vector3 position = PCGEngine2Unity.PCGEngineVectorToUnity(nodePosition);
                GameObject n = Instantiate(node, nodeParent);
                n.transform.position = position;
            }

            GenerationParameters generationParameters = new GenerationParameters()
            {
                count = nodeCount,
                size = size,
                startPoint = PCGEngine2Unity.UnityToPCGEngineVector(startPosition.value)
            };

            PCGEngine.MultiDimensionalGeneration(ref generationParameters, (Axis)axesField.value, disableOverlapToggle.value, AddNode);
        }
    }
}
