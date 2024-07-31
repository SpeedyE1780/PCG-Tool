using System.Runtime.InteropServices;

namespace PCGAPI
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector3
    {
        public float x;
        public float y;
        public float z;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct GenerationParameters
    {
        public uint count;
        public float size;
        public Vector3 startPoint;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct SequenceNode
    {
        public int possibilitiesCount;
    }
}
