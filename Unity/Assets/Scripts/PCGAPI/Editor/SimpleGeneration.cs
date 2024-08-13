using System.Collections;
using System.Collections.Generic;
using Unity.EditorCoroutines.Editor;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    public class SimpleGeneration : EditorWindow
    {
        [SerializeField]
        private VisualTreeAsset m_VisualTreeAsset = default;

        private ObjectField nodeField;
        private UnsignedIntegerField nodeCountField;
        private FloatField nodeSizeField;
        private DropdownField axisField;
        private Vector3Field startPosition;
        private Toggle frameByFrameToggle;

        private GameObject node;
        private Transform nodeParent;

        [MenuItem("PCG/Simple Generation")]
        public static void OpenWindow()
        {
            SimpleGeneration wnd = GetWindow<SimpleGeneration>();
            wnd.titleContent = new GUIContent("Simple Generation");
        }

        public void CreateGUI()
        {
            // Instantiate UXML
            VisualElement uxmlElements = m_VisualTreeAsset.Instantiate();
            rootVisualElement.Add(uxmlElements);

            nodeField = rootVisualElement.Q<ObjectField>("Node");
            nodeCountField = rootVisualElement.Q<UnsignedIntegerField>("Count");
            nodeSizeField = rootVisualElement.Q<FloatField>("Size");
            axisField = rootVisualElement.Q<DropdownField>("Axis");
            startPosition = rootVisualElement.Q<Vector3Field>("StartPosition");
            frameByFrameToggle = rootVisualElement.Q<Toggle>("FramebyFrame");

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

            node = nodeField.value as GameObject;
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

            nodeParent = new GameObject("Simple Generation").transform;

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

                PCGEngine.SimpleGeneration(ref generationParameters, (Axis)(1 << axisField.index), AddNodePosition);
                EditorCoroutineUtility.StartCoroutine(GenerateLevel(positions), this);
            }
            else
            {
                PCGEngine.SimpleGeneration(ref generationParameters, (Axis)(1 << axisField.index), AddNode);
            }
        }

        private void AddNode(Vector3 nodePosition)
        {
            UnityEngine.Vector3 position = PCGEngine2Unity.PCGEngineVectorToUnity(nodePosition);
            GameObject n = Instantiate(node, nodeParent);
            n.transform.position = position;
        }

        private IEnumerator GenerateLevel(List<Vector3> nodes)
        {
            foreach (Vector3 node in nodes)
            {
                AddNode(node);
                yield return null;
            }
        }
    }
}
