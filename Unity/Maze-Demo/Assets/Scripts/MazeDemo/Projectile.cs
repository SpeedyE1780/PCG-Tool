using UnityEngine;

namespace MazeDemo
{
    public class Projectile : MonoBehaviour
    {
        [SerializeField]
        private Rigidbody rb;
        [SerializeField]
        private float speed = 20;
        [SerializeField]
        private float lifeTime = 3;

        private void Start()
        {
            Destroy(gameObject, lifeTime);
        }

        void Update()
        {
            rb.linearVelocity = transform.forward * speed;
        }

        private void OnTriggerEnter(Collider other)
        {
            if(other.attachedRigidbody.CompareTag("Player"))
            {
                Destroy(gameObject);
            }
        }
    }
}
