using PCGAPI.Generators;
using Unity.EditorCoroutines.Editor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    public class CommonGenerationFields<GeneratorType, SpawnedObject> where GeneratorType : Generator<SpawnedObject> where SpawnedObject : Object
    {
        private readonly ObjectField generatorField;
        private readonly ObjectField cellField;
        private readonly UnsignedIntegerField seedField;
        private readonly UnsignedIntegerField cellLimitField;
        private readonly FloatField cellSizeField;
        private readonly Vector3Field startPositionField;
        private readonly Toggle frameToggle;
        private readonly Spawn<SpawnedObject> spawnFunction;

        public SpawnedObject Node { get; private set; }
        public Transform NodeParent { get; private set; }

        public CommonGenerationFields(VisualElement root, Spawn<SpawnedObject> spawnFunction)
        {
            generatorField = root.Q<ObjectField>("Generator");
            cellField = root.Q<ObjectField>("Cell");
            seedField = root.Q<UnsignedIntegerField>("Seed");
            cellLimitField = root.Q<UnsignedIntegerField>("CellLimit");
            cellSizeField = root.Q<FloatField>("CellSize");
            startPositionField = root.Q<Vector3Field>("StartPosition");
            frameToggle = root.Q<Toggle>("FrameToggle");

            var generateButton = root.Q<Button>("GenerateButton");
            generateButton.clicked += SpawnObject;
            this.spawnFunction = spawnFunction;
        }

        private void SpawnObject()
        {
            void Log(string msg)
            {
                Debug.Log(msg);
            }

            PCGEngine.SetLoggingFunction(Log);
            GeneratorType generator = generatorField.value as GeneratorType;
            Node = cellField.value as SpawnedObject;
            uint seed = seedField.value;
            uint limit = cellLimitField.value;
            float size = cellSizeField.value;
            Vector3 startPosition = startPositionField.value;

            if (generator == null)
            {
                Debug.LogWarning("Generator not set");
                return;
            }

            if (Node == null)
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

            NodeParent = new GameObject("GENERATED NODES").transform;

            var data = new GeneratorData(limit, size, startPosition);

            if (frameToggle.value)
            {
                EditorCoroutineUtility.StartCoroutine(generator.GenerateFrameByFrame(data, spawnFunction), this);
            }
            else
            {
                generator.GenerateOneShot(data, spawnFunction);
            }
        }
    }
}
