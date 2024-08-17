using PCGAPI;
using UnityEngine;

namespace MazeDemo
{
    public class MazeSpawner : MonoBehaviour
    {
        [Header("Maze Configuration")]
        [SerializeField]
        private Vector2Int gridSize;
        [SerializeField]
        MazeAlgorithm algorithm;
        [SerializeField]
        private GameObject mazeNode;
        [SerializeField]
        private float nodeSize;
        [SerializeField]
        private uint seed;

        [Header("Game Configuration")]
        [SerializeField]
        private GameObject player;
        [SerializeField]
        private GameObject endPointPrefab;
        [SerializeField]
        private FollowTarget followCamera;
        [SerializeField]
        private Vector2Int startPoint;
        [SerializeField]
        private Vector2Int endPoint;

        private void Start()
        {
            PCGEngine.SetSeed(seed);
            GenerateMaze();
        }

        private void GenerateMaze()
        {
            Transform mazeParent = new GameObject("Maze").transform;
            mazeParent.SetParent(transform);

            PCGEngine.GenerateMaze(gridSize.x, gridSize.y, true, algorithm, (x, y, direction) =>
            {
                UnityEngine.Vector3 position = new UnityEngine.Vector3(x * nodeSize, 0, y * nodeSize);
                IMazeNode node = Instantiate(mazeNode, mazeParent).GetComponent<IMazeNode>();
                node.SetAdjacentNodes(direction);
                node.transform.position = position;

                if (x == startPoint.x && y == startPoint.y)
                {
                    GameObject spawnedPlayer = Instantiate(player, position, Quaternion.identity);
                    followCamera.Target = spawnedPlayer.transform;
                }

                if (x == endPoint.x && y == endPoint.y)
                {
                    Instantiate(endPointPrefab, position, Quaternion.identity);
                }
            });
        }
    }
}
