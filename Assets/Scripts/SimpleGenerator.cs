using UnityEngine;

[CreateAssetMenu(fileName = "SimpleGenerator", menuName = "Scriptable Objects/PCG/SimpleGenerator")]
public class SimpleGenerator : ScriptableObject
{
    [SerializeField]
    private GameObject cellPrefab;
    [SerializeField]
    private int cellLimit;
    [SerializeField]
    private float cellSize;

    public void Generate()
    {
        Vector3 startPosition = Vector3.zero;
        for (int i = 0; i < cellLimit; i++)
        {
            Vector3 position = startPosition + Vector3.forward * i;
            Instantiate(cellPrefab, position, Quaternion.identity);
        }
    }
}
