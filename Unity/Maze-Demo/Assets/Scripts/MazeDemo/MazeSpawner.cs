using PCGAPI;
using PCGAPI.Demo;
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
                bool spawnPlayer = x == startPoint.x && y == startPoint.y;

                if (spawnPlayer)
                {
                    GameObject spawnedPlayer = Instantiate(player, position, Quaternion.identity);
                    followCamera.Target = spawnedPlayer.transform;
                }

                if (x == endPoint.x - 1 && y == endPoint.y - 1)
                {
                    Instantiate(endPointPrefab, position, Quaternion.identity);
                }

                IMazeNode node = Instantiate(mazeNode, mazeParent).GetComponent<IMazeNode>();

                if ((MazeNode)node != null)
                {
                    ((MazeNode)node).SpawnTurret = !spawnPlayer;
                }

                node.SetAdjacentNodes(direction);
                node.transform.position = position;
            });
        }
    }
}
