using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "2DGenerator", menuName = "Scriptable Objects/PCG/2DGenerator")]
public class Generator2D : Generator
{
    [SerializeField]
    private PCGEngine2Unity.Plane plane;
    [SerializeField]
    private bool disableOverlap;

    private List<Vector3> directions;
    private HashSet<Vector3> cellPositions;

    private void InitializeDirections()
    {
        switch (plane)
        {
            case PCGEngine2Unity.Plane.XY:
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
            case PCGEngine2Unity.Plane.XZ:
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
            case PCGEngine2Unity.Plane.YZ:
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

    private List<Vector3> GetNextPositions(Vector3 currentPosition)
    {
        List<Vector3> positions = new List<Vector3>();

        foreach (Vector3 direction in directions)
        {
            Vector3 nextPosition = currentPosition + direction;

            if (!cellPositions.Contains(nextPosition))
            {
                positions.Add(nextPosition);
            }
        }

        return positions;
    }

    public override IEnumerator Generate(GeneratorData data)
    {
        List<Vector3> points = new List<Vector3>();

        PCGEngine2Unity.GeneratorData generator = new PCGEngine2Unity.GeneratorData()
        {
            limit = data.limit,
            size = data.size,
            startPoint = PCGEngine2Unity.Unity2PCGEngineVector(data.startPosition)
        };

        PCGEngine2Unity.Generator2D(ref generator, plane, disableOverlap, (vector) =>
        {
            points.Add(PCGEngine2Unity.PCGEngineVectorToUnity(vector));
        });

        foreach (Vector3 point in points)
        {
            SpawnCell(data.cell, point);
            yield return null;
        }
    }
}
