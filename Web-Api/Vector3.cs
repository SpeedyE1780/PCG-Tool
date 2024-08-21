namespace PCGAPI.WebAPI
{
    public record Vector3(float X, float Y, float Z)
    {
    }

    public static class Vector3Helper
    {
        public static Vector3 ToWebAPI(PCGAPI.Vector3 vector) => new(vector.x, vector.y, vector.z);
        public static PCGAPI.Vector3 ToEngine(Vector3 vector) => new(vector.X, vector.Y, vector.Z);
    }
}
