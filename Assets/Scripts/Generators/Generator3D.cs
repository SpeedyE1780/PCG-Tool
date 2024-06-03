using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "Generator3D", menuName = "Scriptable Objects/PCG/Generator3D")]
public class Generator3D : Generator
{
    [SerializeField]
    private bool disableOverlap;

    private List<Vector3> directions;
    private HashSet<Vector3> cellPositions;

    private void InitializeDirections()
    {
        directions = new List<Vector3>()
                    {
                        Vector3.right,
                        Vector3.left,
                        Vector3.up,
                        Vector3.down,
                        Vector3.forward,
                        Vector3.back
                    };
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

            List<Vector3> nextPositions = GetNextPositions(position);

            if (nextPositions.Count == 0)
            {
                Debug.LogWarning("No more available position without overlapping ending generation early");
                return;
            }

            position = nextPositions[Random.Range(0, nextPositions.Count)];
        }
    }
}
