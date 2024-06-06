using System.Runtime.InteropServices;

namespace PCGAPI
{
    public static class PCGEngine
    {
        public delegate void AddPosition(Vector3 position);

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

        public enum Plane
        {
            XY = 0,
            XZ = 1,
            YZ = 2
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
        public struct GenerationParameters
        {
            public uint limit;
            public float size;
            public Vector3 startPoint;
        }

        [DllImport("PCG-Engine-Core", EntryPoint = "simpleGeneration")]
        public static extern void SimpleGenerator(ref GenerationParameters data, Axis axis, Direction direction, AddPosition createVector);
        [DllImport("PCG-Engine-Core", EntryPoint = "generation2D")]
        public static extern void Generator2D(ref GenerationParameters data, Plane plane, bool disableOverlap, AddPosition createVector);
        [DllImport("PCG-Engine-Core", EntryPoint = "generation3D")]
        public static extern void Generator3D(ref GenerationParameters data, bool disableOverlap, AddPosition createVector);
        [DllImport("PCG-Engine-Core", EntryPoint = "setSeed")]
        public static extern void UpdateSeed(uint seed);
    }
}
