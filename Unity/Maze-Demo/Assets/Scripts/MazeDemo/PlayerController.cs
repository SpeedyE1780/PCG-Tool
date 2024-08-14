using UnityEngine;

namespace MazeDemo
{
    public class PlayerController : MonoBehaviour
    {
        [SerializeField]
        private Rigidbody rb;
        [SerializeField]
        private float speed;

        private Vector3 velocity = new Vector3();

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
            rb.MoveRotation(Quaternion.LookRotation(velocity, Vector3.up));
        }
    }
}
