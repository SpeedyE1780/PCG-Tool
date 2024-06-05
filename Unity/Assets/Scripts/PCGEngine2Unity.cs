using System.Runtime.InteropServices;
using UnityEngine;

public static class PCGEngine2Unity
{
    [DllImport("PCG-Engine-Core", EntryPoint = "?add@core@engine@pcg@@YAHHH@Z")]
    public static extern int Add(int x, int y);
}
