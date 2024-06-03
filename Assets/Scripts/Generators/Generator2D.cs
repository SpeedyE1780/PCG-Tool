using UnityEngine;

[CreateAssetMenu(fileName = "2DGenerator", menuName = "Scriptable Objects/PCG/2DGenerator")]
public class Generator2D : Generator
{
    private Vector3 GetNextDirection()
    {
        int number = Random.Range(0, 5);

        return number switch
        {
            0 => Vector3.right,
            1 => Vector3.left,
            2 => Vector3.forward,
            3 => Vector3.back,
            _ => Vector3.zero
        };
    }

    public override void Generate(in GeneratorData data)
    {
        Vector3 position = data.startPosition;

        for (int i = 0; i < data.limit; i++)
        {
            SpawnCell(data.cell, position);
            position += GetNextDirection() * data.size;
        }
    }
}
