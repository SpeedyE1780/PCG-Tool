using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI.Generators
{
    public abstract class Generator : ScriptableObject
    {
        public delegate GameObject Spawn(Vector3 position);

        private readonly List<Vector3> spawnPoints = new List<Vector3>();

        protected Spawn SpawnFunction { get; private set; }

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

        protected virtual GameObject SpawnThing(Vector3 position)
        {
            return SpawnFunction(position);
        }

        public void GenerateOneShot(GeneratorData data, Spawn spawnFunction)
        {
            PCGEngine.GenerationParameters parameters = PCGEngine2Unity.GeneratorDataToPCGEngineGenerationParameters(data);
            SpawnFunction = spawnFunction;
            GenerateLevel(ref parameters);

            foreach (Vector3 point in spawnPoints)
            {
                SpawnThing(point);
            }
        }

        public IEnumerator GenerateFrameByFrame(GeneratorData data, Spawn spawnFunction)
        {
            PCGEngine.GenerationParameters parameters = PCGEngine2Unity.GeneratorDataToPCGEngineGenerationParameters(data);
            SpawnFunction = spawnFunction;
            GenerateLevel(ref parameters);

            foreach (Vector3 point in spawnPoints)
            {
                SpawnThing(point);
                yield return null;
            }
        }
    }
}
