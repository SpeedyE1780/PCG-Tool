using System.Runtime.InteropServices;

public static class PCGEngine2Unity
{
    public delegate void AddPosition(float x, float y, float z);

    [DllImport("PCG-Engine-Core", EntryPoint = "?add@core@engine@pcg@@YAHHH@Z")]
    public static extern int Add(int x, int y);
    [DllImport("PCG-Engine-Core", EntryPoint = "?simpleGeneration@core@engine@pcg@@YAXP6AXMMM@Z@Z")]
    public static extern void SimpleGenerator(AddPosition createVector);
}
