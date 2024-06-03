using UnityEngine;

[CreateAssetMenu(fileName = "SimpleGenerator", menuName = "Scriptable Objects/PCG/SimpleGenerator")]
public class SimpleGenerator : ScriptableObject
{
    public void Generate(in GeneratorData data)
    {
        for (int i = 0; i < data.limit; i++)
        {
            Vector3 position = data.startPosition + data.size * i * Vector3.forward;
            Instantiate(data.cell, position, Quaternion.identity);
        }
    }
}
