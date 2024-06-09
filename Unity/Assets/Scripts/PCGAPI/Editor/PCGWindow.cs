using PCGAPI.Generators;
using Unity.EditorCoroutines.Editor;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    public class PCGWindow : EditorWindow
    {
        [SerializeField]
        private VisualTreeAsset m_VisualTreeAsset = default;

        private ObjectField generatorField;
        private ObjectField cellField;
        private UnsignedIntegerField seedField;
        private UnsignedIntegerField cellLimitField;
        private FloatField cellSizeField;
        private Vector3Field startPositionField;
        private Toggle frameToggle;

        [MenuItem("PCG/Open Window")]
        public static void OpenWindow()
        {
            PCGWindow wnd = GetWindow<PCGWindow>();
            wnd.titleContent = new GUIContent("PCG Window");
        }

        public void CreateGUI()
        {
            // Each editor window contains a root VisualElement object
            VisualElement root = rootVisualElement;

            // Instantiate UXML
            VisualElement labelFromUXML = m_VisualTreeAsset.Instantiate();
            root.Add(labelFromUXML);

            generatorField = root.Q<ObjectField>("Generator");
            cellField = root.Q<ObjectField>("Cell");
            seedField = root.Q<UnsignedIntegerField>("Seed");
            cellLimitField = root.Q<UnsignedIntegerField>("CellLimit");
            cellSizeField = root.Q<FloatField>("CellSize");
            startPositionField = root.Q<Vector3Field>("StartPosition");
            frameToggle = root.Q<Toggle>("FrameToggle");

            var generateButton = root.Q<Button>("GenerateButton");
            generateButton.clicked += SpawnObject;
        }

        private void SpawnObject()
        {
            Generator generator = generatorField.value as Generator;
            GameObject cell = cellField.value as GameObject;
            uint seed = seedField.value;
            uint limit = cellLimitField.value;
            float size = cellSizeField.value;
            Vector3 startPosition = startPositionField.value;

            if (generator == null)
            {
                Debug.LogWarning("Generator not set");
                return;
            }

            if (cell == null)
            {
                Debug.LogWarning("Cell not set");
                return;
            }

            if (limit == 0)
            {
                Debug.LogWarning("Limit is zero nothing to generate");
                return;
            }

            if (size == 0)
            {
                Debug.LogWarning("Cell size is 0 object will spawn on top of one another");
                return;
            }

            void SetSeed(uint seed)
            {
                Debug.Log("SET SEED");
                Random.InitState((int)seed);
            }

            int Generate(int min, int max)
            {
                Debug.Log("GENERATING");
                return Random.Range(min, max);
            }

            PCGEngine.SetRandomGenerators(SetSeed, Generate);
            PCGEngine.UpdateSeed(seed);

            void SpawnFunction(Vector3 position)
            {
                GameObject go = null;

                if (PrefabUtility.IsPartOfAnyPrefab(cell))
                {
                    go = PrefabUtility.InstantiatePrefab(cell) as GameObject;
                    go.transform.position = position;
                }
                else
                {
                    go = Instantiate(cell, position, Quaternion.identity);
                }

                Undo.RegisterCreatedObjectUndo(go, "Spawned cell");
            }

            if (frameToggle.value)
            {
                EditorCoroutineUtility.StartCoroutine(generator.GenerateFrameByFrame(new GeneratorData(limit, size, startPosition), SpawnFunction), this); 
            }
            else
            {
                generator.GenerateOneShot(new GeneratorData(limit, size, startPosition), SpawnFunction);
            }
        }
    }
}
