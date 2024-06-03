using UnityEditor;
using UnityEngine;

[CreateAssetMenu(fileName = "SimpleGenerator", menuName = "Scriptable Objects/PCG/SimpleGenerator")]
public class SimpleGenerator : ScriptableObject
{
    private enum Axis
    {
        x,
        y,
        z
    }

    private enum Direction
    {
        positive,
        negative
    }

    [SerializeField]
    private Axis axis;
    [SerializeField]
    private Direction direction;

    private Vector3 GetDirection()
    {
        return axis switch
        {
            Axis.x => direction == Direction.positive ? Vector3.right : Vector3.left,
            Axis.y => direction == Direction.positive ? Vector3.up : Vector3.down,
            Axis.z => direction == Direction.positive ? Vector3.forward : Vector3.back,
            _ => Vector3.zero,
        };
    }

    private void SpawnCell(GameObject cell, Vector3 position)
    {
        GameObject go = null;

        if (PrefabUtility.IsPartOfAnyPrefab(cell))
        {
            go = PrefabUtility.InstantiatePrefab(cell) as GameObject;
            go.transform.position = position;
        }
        else
        {
            go = Instantiate(cell, position, Quaternion.identity);
        }

        Undo.RegisterCreatedObjectUndo(go, "Spawned cell");
    }

    public void Generate(in GeneratorData data)
    {
        Vector3 direction = GetDirection();

        for (int i = 0; i < data.limit; i++)
        {
            Vector3 position = data.startPosition + data.size * i * direction;
            SpawnCell(data.cell, position);
        }
    }
}
