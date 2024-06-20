using PCGAPI.Generators;

namespace PCGAPI
{
    public static class PCGEngine2Unity
    {
        public static Vector3 UnityToPCGEngineVector(UnityEngine.Vector3 vector)
        {
            return new Vector3(vector.x, vector.y, vector.z);
        }

        public static UnityEngine.Vector3 PCGEngineVectorToUnity(Vector3 vector)
        {
            return new UnityEngine.Vector3(vector.x, vector.y, vector.z);
        }

        public static GenerationParameters GeneratorDataToPCGEngineGenerationParameters(GeneratorData generatorData)
        {
            return new GenerationParameters()
            {
                count = generatorData.limit,
                size = generatorData.size,
                startPoint = UnityToPCGEngineVector(generatorData.startPosition)
            };
        }
    }
}
