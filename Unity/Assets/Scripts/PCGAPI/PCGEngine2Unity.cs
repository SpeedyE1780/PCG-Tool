using PCGAPI.Generators;

namespace PCGAPI
{
    public static class PCGEngine2Unity
    {
        public static PCGEngine.Vector3 UnityToPCGEngineVector(UnityEngine.Vector3 vector)
        {
            return new PCGEngine.Vector3(vector.x, vector.y, vector.z);
        }

        public static UnityEngine.Vector3 PCGEngineVectorToUnity(PCGEngine.Vector3 vector)
        {
            return new UnityEngine.Vector3(vector.x, vector.y, vector.z);
        }

        public static PCGEngine.GenerationParameters GeneratorDataToPCGEngineGenerationParameters(GeneratorData generatorData)
        {
            return new PCGEngine.GenerationParameters()
            {
                limit = generatorData.limit,
                size = generatorData.size,
                startPoint = UnityToPCGEngineVector(generatorData.startPosition)
            };
        }
    }
}
