namespace PCGAPI
{
    /// <summary>
    /// PCGEngine2Unity is used to convert Vector3 from PCGAPI.Vector3 to UnityEngine.Vector3
    /// </summary>
    public static class PCGEngine2Unity
    {
        /// <summary>
        /// Convert Unity Vector3 to PCG Vector3
        /// </summary>
        /// <param name="vector">Unity Vector3</param>
        /// <returns>Equivalent PCG Vector3</returns>
        public static Vector3 UnityToPCGEngineVector(UnityEngine.Vector3 vector)
        {
            return new Vector3(vector.x, vector.y, vector.z);
        }

        /// <summary>
        /// Convert PCG Vector3 to Unity Vector3
        /// </summary>
        /// <param name="vector">PCG Vector3</param>
        /// <returns>Equivalent Unity Vector3</returns>
        public static UnityEngine.Vector3 PCGEngineVectorToUnity(Vector3 vector)
        {
            return new UnityEngine.Vector3(vector.x, vector.y, vector.z);
        }

        public static Vector4 UnityToPCGEngineVector(UnityEngine.Vector4 vector)
        {
            return new Vector4(vector.x, vector.y, vector.z, vector.w);
        }

        public static UnityEngine.Vector4 PCGEngineVectorToUnity(Vector4 vector)
        {
            return new UnityEngine.Vector4(vector.x, vector.y, vector.z, vector.w);
        }
    }
}
