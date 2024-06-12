using System.Runtime.InteropServices;

namespace PCGAPI
{
    public static class PCGEngine
    {
        public delegate void AddPosition(Vector3 position);
        public delegate void AddWFCPosition(Vector3 position, int neighbors);
        public delegate void SetSeed(uint seed);
        public delegate int GenerateNumber(int min, int max);
        public delegate void LogFunction(string message);
        public delegate void AddMazePosition(int x, int y, int neighbors);

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

        public enum ExpansionMode
        {
            BFS,
            DFS
        };

        [DllImport("PCG-Engine-Core", EntryPoint = "generation1D")]
        public static extern void SimpleGenerator(ref GenerationParameters data, Axis axis, Direction direction, AddPosition addPosition);
        [DllImport("PCG-Engine-Core", EntryPoint = "generation2D")]
        public static extern void Generator2D(ref GenerationParameters data, Plane plane, bool disableOverlap, AddPosition addPosition);
        [DllImport("PCG-Engine-Core", EntryPoint = "generation3D")]
        public static extern void Generator3D(ref GenerationParameters data, bool disableOverlap, AddPosition addPosition);
        [DllImport("PCG-Engine-Core", EntryPoint = "setSeed")]
        public static extern void UpdateSeed(uint seed);
        [DllImport("PCG-Engine-Core", EntryPoint = "setRandomGenerator")]
        public static extern void SetRandomGenerators(SetSeed setSeed, GenerateNumber generate);
        [DllImport("PCG-Engine-Core", EntryPoint = "setLoggingFunction")]
        public static extern void SetLoggingFunction(LogFunction logFunction);
        [DllImport("PCG-Engine-Core", EntryPoint = "waveFunctionCollapseGeneration")]
        public static extern void WaveFunctionCollapse(ref GenerationParameters data, ExpansionMode mode, AddWFCPosition addPosition);
        [DllImport("PCG-Engine-Core", EntryPoint = "generateMaze")]
        public static extern void GenerateMaze(int width, int height, AddMazePosition addMazePosition);
    }
}
