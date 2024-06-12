using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI.Generators
{
    public delegate T Spawn<T>(Vector3 position);

    public abstract class Generator<T> : ScriptableObject
    {
        private readonly List<Vector3> spawnPoints = new List<Vector3>();
        private Spawn<T> spawnFunction;

        protected void AddSpawnPoint(PCGEngine.Vector3 position)
        {
            spawnPoints.Add(PCGEngine2Unity.PCGEngineVectorToUnity(position));
        }

        protected abstract void GenerateWithEngine(ref PCGEngine.GenerationParameters parameters);

        private void GenerateLevel(ref PCGEngine.GenerationParameters parameters)
        {
            spawnPoints.Clear();
            GenerateWithEngine(ref parameters);
        }

        protected virtual T SpawnThing(Vector3 position)
        {
            return spawnFunction(position);
        }

        public void GenerateOneShot(GeneratorData data, Spawn<T> spawn)
        {
            PCGEngine.GenerationParameters parameters = PCGEngine2Unity.GeneratorDataToPCGEngineGenerationParameters(data);
            spawnFunction = spawn;
            GenerateLevel(ref parameters);

            foreach (Vector3 point in spawnPoints)
            {
                SpawnThing(point);
            }
        }

        public IEnumerator GenerateFrameByFrame(GeneratorData data, Spawn<T> spawn)
        {
            PCGEngine.GenerationParameters parameters = PCGEngine2Unity.GeneratorDataToPCGEngineGenerationParameters(data);
            spawnFunction = spawn;
            GenerateLevel(ref parameters);

            foreach (Vector3 point in spawnPoints)
            {
                SpawnThing(point);
                yield return null;
            }
        }
    }
}
