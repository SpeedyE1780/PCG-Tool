using UnityEditor;
using UnityEngine;

public abstract class Generator : ScriptableObject
{
    protected void SpawnCell(GameObject cell, Vector3 position)
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

    public abstract void Generate(in GeneratorData data);
}
