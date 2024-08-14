using UnityEngine;

namespace MazeDemo
{
    public class Turret : MonoBehaviour
    {
        [SerializeField]
        private Transform headTransform;
        [SerializeField]
        private float range = 5f;
        [SerializeField]
        private float rotationSpeed = 30f;
        [SerializeField]
        private LayerMask mask;

        private Transform target;
        private readonly Collider[] targetCollider = new Collider[1];

        private void Update()
        {
            if (Physics.OverlapSphereNonAlloc(transform.position, range, targetCollider, mask) > 0)
            {
                target = targetCollider[0].transform;
            }

            if (target != null)
            {
                Vector3 forward = target.position - transform.position;
                forward.y = 0f;

                headTransform.rotation = Quaternion.RotateTowards(headTransform.rotation, Quaternion.LookRotation(forward, Vector3.up), rotationSpeed * Time.deltaTime);
            }
        }

        private void OnDrawGizmos()
        {
            Gizmos.DrawWireSphere(transform.position, range);
        }
    }
}
