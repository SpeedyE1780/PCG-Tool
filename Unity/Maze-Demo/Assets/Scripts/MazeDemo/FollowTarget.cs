using UnityEngine;

namespace MazeDemo
{
    public class FollowTarget : MonoBehaviour
    {
        [SerializeField]
        private Transform target;
        [SerializeField]
        private Vector3 offset;
        [SerializeField]
        private bool localSpace;

        public Transform Target { get { return target; } set { target = value; } }

        void LateUpdate()
        {
            if (localSpace)
            {
                transform.position = target.TransformPoint(offset);
            }
            else
            {
                transform.position = target.position + offset;
            }

            transform.forward = target.position - transform.position;
        }
    }
}
