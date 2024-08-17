using System.Collections;
using UnityEngine;
using UnityEngine.AI;

namespace MazeDemo
{
    public class ChaserController : MonoBehaviour
    {
        [SerializeField]
        private NavMeshAgent agent;
        [SerializeField]
        private Transform target;
        [SerializeField]
        private float maxSpeed;
        [SerializeField]
        private float acceleration;
        [SerializeField]
        private float delay;
        [SerializeField]
        private float distanceThreshold;

        private bool chasing;

        private IEnumerator Start()
        {
            yield return new WaitForSeconds(delay);
            StartCoroutine(Chase());
        }

        private void OnEnable()
        {
            PlayerController.OnReachEnd += PlayerReachEnd;
        }
        private void OnDisable()
        {
            PlayerController.OnReachEnd -= PlayerReachEnd;
        }

        private void PlayerReachEnd()
        {
            chasing = false;
            agent.SetDestination(transform.position);
        }


        private IEnumerator Chase()
        {
            chasing = true;

            while (chasing)
            {
                agent.SetDestination(target.position);
                agent.speed = Mathf.MoveTowards(agent.speed, maxSpeed, acceleration * Time.deltaTime);

                if (!agent.pathPending && agent.remainingDistance < distanceThreshold)
                {
                    Destroy(target.gameObject);
                    yield break;
                }

                yield return null;
            }
        }
    }
}
