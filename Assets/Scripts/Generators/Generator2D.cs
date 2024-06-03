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
    [SerializeField]
    private bool disableOverlap;

    private List<Vector3> directions;
    private HashSet<Vector3> cellPositions;

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
        if (disableOverlap)
        {
            cellPositions = new HashSet<Vector3>();
        }

        InitializeDirections();
        Vector3 position = data.startPosition;

        for (int i = 0; i < data.limit; i++)
        {
            if (disableOverlap)
            {
                cellPositions.Add(position);
            }

            SpawnCell(data.cell, position);


            Vector3 tempPosition = position;

            do
            {
                tempPosition = position;
                tempPosition += GetNextDirection() * data.size;
            } while (cellPositions.Contains(tempPosition));

            position = tempPosition;
        }
    }
}
