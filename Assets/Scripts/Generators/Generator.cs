using UnityEngine;

public abstract class Generator : ScriptableObject
{
    public abstract void Generate(in GeneratorData data);
}
