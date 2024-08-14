using UnityEngine;

namespace MazeDemo
{
    public class PlayerController : MonoBehaviour
    {
        public delegate void PlayerHit(Transform playerTransform);

        [SerializeField]
        private Rigidbody rb;
        [SerializeField]
        private float speed;

        private Vector3 velocity = new Vector3();
        private Vector3 startPosition;

        public static PlayerHit OnPlayerHitEvent;

        private void Start()
        {
            startPosition = transform.position;
        }

        private void OnEnable()
        {
            OnPlayerHitEvent += OnPlayerHit;
        }

        private void OnDisable()
        {
            OnPlayerHitEvent -= OnPlayerHit;
        }

        private void OnPlayerHit(Transform playerTransform)
        {
            if(playerTransform == transform)
            {
                transform.position = startPosition;
            }
        }

        void Update()
        {
            velocity.x = Input.GetAxis("Horizontal");
            velocity.y = 0;
            velocity.z = Input.GetAxis("Vertical");

            velocity.Normalize();
            velocity *= speed;
            velocity.y = rb.linearVelocity.y;
        }

        private void FixedUpdate()
        {
            rb.linearVelocity = velocity;
            velocity.y = 0;

            if (velocity.sqrMagnitude > 0)
            {
                rb.MoveRotation(Quaternion.LookRotation(velocity, Vector3.up)); 
            }
        }
    }
}
