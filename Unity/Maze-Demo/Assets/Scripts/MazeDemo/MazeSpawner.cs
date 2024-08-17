using PCGAPI;
using PCGAPI.Demo;
using System.Collections;
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

        private Transform mazeParent;

        private void Start()
        {
            PCGEngine.SetSeed(seed);
            GenerateMaze();
        }

        private void OnEnable()
        {
            PlayerController.OnReachEnd += OnReachEnd;
        }

        private void OnDisable()
        {
            PlayerController.OnReachEnd -= OnReachEnd;
        }

        private void OnReachEnd()
        {
            StartCoroutine(SpawnNewMaze());
        }

        private IEnumerator SpawnNewMaze()
        {
            Destroy(mazeParent.gameObject);
            yield return null;
            GenerateMaze();
        }

        private void GenerateMaze()
        {
            mazeParent = new GameObject("Maze").transform;
            mazeParent.SetParent(transform);

            PCGEngine.GenerateMaze(gridSize.x, gridSize.y, true, algorithm, (x, y, direction) =>
            {
                UnityEngine.Vector3 position = new UnityEngine.Vector3(x * nodeSize, 0, y * nodeSize);
                bool spawnPlayer = x == startPoint.x && y == startPoint.y;

                if (spawnPlayer)
                {
                    GameObject spawnedPlayer = Instantiate(player, position, Quaternion.identity);
                    spawnedPlayer.transform.SetParent(transform);
                    followCamera.Target = spawnedPlayer.transform;
                }

                if (x == endPoint.x - 1 && y == endPoint.y - 1)
                {
                    GameObject endPoint = Instantiate(endPointPrefab, position, Quaternion.identity);
                    endPoint.transform.SetParent(transform);
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
