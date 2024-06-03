using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "2DGenerator", menuName = "Scriptable Objects/PCG/2DGenerator")]
public class Generator2D : Generator
{
    private enum Plane
    {
        xy,
        xz,
        yz
    }

    [SerializeField]
    private Plane plane;

    private List<Vector3> directions;

    private void InitializeDirections()
    {
        switch (plane)
        {
            case Plane.xy:
                {
                    directions = new List<Vector3>()
                    {
                        Vector3.right,
                        Vector3.left,
                        Vector3.up,
                        Vector3.down
                    };

                    break;
                }
            case Plane.xz:
                {
                    directions = new List<Vector3>()
                    {
                        Vector3.right,
                        Vector3.left,
                        Vector3.forward,
                        Vector3.back
                    };

                    break;
                }
            case Plane.yz:
                {
                    directions = new List<Vector3>()
                    {
                        Vector3.up,
                        Vector3.down,
                        Vector3.forward,
                        Vector3.back
                    };

                    break;
                }
        }
    }

    private Vector3 GetNextDirection()
    {
        return directions[Random.Range(0, directions.Count)];
    }

    public override void Generate(in GeneratorData data)
    {
        InitializeDirections();
        Vector3 position = data.startPosition;

        for (int i = 0; i < data.limit; i++)
        {
            SpawnCell(data.cell, position);
            position += GetNextDirection() * data.size;
        }
    }
}
