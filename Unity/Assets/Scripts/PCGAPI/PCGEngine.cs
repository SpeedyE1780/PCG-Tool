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

        [System.Flags]
        public enum Axis
        {
            x = 1 << 0,
            y = 1 << 1,
            z = 1 << 2
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

        public enum MazeAlgorithm
        {
            aldousBroder = 0,
            wilson = 1
        }

        [DllImport("PCG-Engine-C-API", EntryPoint = "simpleGeneration")]
        public static extern void SimpleGenerator(ref GenerationParameters data, Axis axis, Direction direction, AddPosition addPosition);
        [DllImport("PCG-Engine-C-API", EntryPoint = "multiDimensionGeneration")]
        public static extern void MultiDimensionGenerator(ref GenerationParameters data, Axis axis, bool disableOverlap, AddPosition addPosition);
        [DllImport("PCG-Engine-C-API", EntryPoint = "setSeed")]
        public static extern void UpdateSeed(uint seed);
        [DllImport("PCG-Engine-C-API", EntryPoint = "setRandomGenerator")]
        public static extern void SetRandomGenerators(SetSeed setSeed, GenerateNumber generate);
        [DllImport("PCG-Engine-C-API", EntryPoint = "setLoggingFunction")]
        public static extern void SetLoggingFunction(LogFunction logFunction);
        [DllImport("PCG-Engine-C-API", EntryPoint = "waveFunctionCollapseGeneration")]
        public static extern void WaveFunctionCollapse(ref GenerationParameters data, ExpansionMode mode, Axis axis, AddWFCPosition addPosition);
        [DllImport("PCG-Engine-C-API", EntryPoint = "generateMaze")]
        public static extern void GenerateMaze(int width, int height, MazeAlgorithm algorithm, AddMazePosition addMazePosition);
    }
}
