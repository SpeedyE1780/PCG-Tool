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
        [SerializeField]
        private Projectile projectile;
        [SerializeField]
        private float cooldown = 0.4f;

        private Transform target;
        private readonly Collider[] targetCollider = new Collider[1];
        private float currentCooldown = 0f;

        private void Update()
        {
            currentCooldown -= Time.deltaTime;

            if (Physics.OverlapSphereNonAlloc(transform.position, range, targetCollider, mask) > 0)
            {
                target = targetCollider[0].transform;
            }
            else
            {
                target = null;
            }

            if (target != null)
            {
                Vector3 forward = target.position - transform.position;
                forward.y = 0f;

                headTransform.rotation = Quaternion.RotateTowards(headTransform.rotation, Quaternion.LookRotation(forward, Vector3.up), rotationSpeed * Time.deltaTime);

                if (Vector3.Angle(headTransform.forward, forward) < 5f && currentCooldown < 0)
                {
                    currentCooldown = cooldown;
                    Instantiate(projectile, headTransform.position, headTransform.rotation);
                }
            }
        }

        private void OnDrawGizmos()
        {
            Gizmos.DrawWireSphere(transform.position, range);
        }
    }
}
