using System.Runtime.InteropServices;

public static class PCGEngine2Unity
{
    public delegate void AddPosition(Vector3 position);

    public static Vector3 Unity2PCGEngineVector(UnityEngine.Vector3 vector)
    {
        return new Vector3(vector.x, vector.y, vector.z);
    }

    public static UnityEngine.Vector3 PCGEngineVectorToUnity(Vector3 vector)
    {
        return new UnityEngine.Vector3(vector.x, vector.y, vector.z);
    }

    public enum Axis
    {
        x = 0,
        y = 1,
        z = 2
    }

    public enum Direction
    {
        positive = 0,
        negative = 1
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Vector3
    {
        public float x;
        public float y;
        public float z;

        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct GeneratorData
    {
        public uint limit;
        public float size;
        public Vector3 startPoint;
    }

    [DllImport("PCG-Engine-Core", EntryPoint = "?add@core@engine@pcg@@YAHHH@Z")]
    public static extern int Add(int x, int y);
    [DllImport("PCG-Engine-Core", EntryPoint = "?simpleGeneration@core@engine@pcg@@YAXPEAUGenerationData@123@W4Axis@123@W4Direction@123@P6AXUVector3@123@@Z@Z")]
    public static extern void SimpleGenerator(ref GeneratorData data, Axis axis, Direction direction, AddPosition createVector);
    [DllImport("PCG-Engine-Core", EntryPoint = "?generation2D@core@engine@pcg@@YAXPEAUGenerationData@123@P6AXUVector3@123@@Z@Z")]
    public static extern void Generator2D(ref GeneratorData data, AddPosition createVector);
}
