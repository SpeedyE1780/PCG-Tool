using System.Runtime.InteropServices;

namespace PCGAPI
{
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
        public uint count;
        public float size;
        public Vector3 startPoint;
    }

    [StructLayout(LayoutKind.Sequential)]
    public class SequenceNode
    {
        public SequenceNode[] nextNodes;
        public int nextCount;
        public int nextNodeIndex = -1;
    }
}
