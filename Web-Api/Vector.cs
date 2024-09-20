namespace PCGAPI.WebAPI
{
    public record Vector3(float X, float Y, float Z)
    {
    }

    public record Vector4(float X, float Y, float Z, float W)
    {
    }

    public static class VectorHelper
    {
        public static Vector3 ToWebAPI(PCGAPI.Vector3 vector) => new(vector.x, vector.y, vector.z);
        public static Vector4 ToWebAPI(PCGAPI.Vector4 vector) => new(vector.x, vector.y, vector.z, vector.w);
        public static PCGAPI.Vector3 ToEngine(Vector3 vector) => new(vector.X, vector.Y, vector.Z);
        public static PCGAPI.Vector4 ToEngine(Vector4 vector) => new(vector.X, vector.Y, vector.Z, vector.W);

    }
}
