using System.Collections;
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

        PCGEngine2Unity.Generator2D(ref generator, (vector) =>
        {
            points.Add(PCGEngine2Unity.PCGEngineVectorToUnity(vector));
        });

        foreach (Vector3 point in points)
        {
            SpawnCell(data.cell, point);
            yield return null;
        }

        //if (disableOverlap)
        //{
        //    cellPositions = new HashSet<Vector3>();
        //}

        //InitializeDirections();
        //Vector3 position = data.startPosition;

        //for (int i = 0; i < data.limit; i++)
        //{
        //    if (disableOverlap)
        //    {
        //        cellPositions.Add(position);
        //    }

        //    SpawnCell(data.cell, position);

        //    List<Vector3> nextPositions = GetNextPositions(position);

        //    if (nextPositions.Count == 0)
        //    {
        //        Debug.LogWarning("No more available position without overlapping ending generation early");
        //        yield break;
        //    }

        //    position = nextPositions[Random.Range(0, nextPositions.Count)];
        //    yield return null;
        //}
    }
}
