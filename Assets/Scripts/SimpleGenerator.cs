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

    [SerializeField]
    private Axis axis;

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
        for (int i = 0; i < data.limit; i++)
        {
            Vector3 position = data.startPosition + data.size * i * Vector3.forward;
            SpawnCell(data.cell, position);
        }
    }
}
