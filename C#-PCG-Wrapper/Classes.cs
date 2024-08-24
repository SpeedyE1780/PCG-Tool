using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace PCGAPI
{
    /// <summary>
    /// Represent a Vector3
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector3
    {
        /// <summary>
        /// Value of x axis
        /// </summary>
        public float x;
        /// <summary>
        /// Value of y axis
        /// </summary>
        public float y;
        /// <summary>
        /// Value of z axis
        /// </summary>
        public float z;

        /// <summary>
        /// Construct a Vector3
        /// </summary>
        /// <param name="x">Value of x axis</param>
        /// <param name="y">Value of y axis</param>
        /// <param name="z">Value of z axis</param>
        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        /// <summary>
        /// Checks for equality between lhs and rhs
        /// </summary>
        /// <param name="lhs">Vector on the left side of ==</param>
        /// <param name="rhs">Vector on the right side of ==</param>
        /// <returns>True if lhs == rhs</returns>
        public static bool operator ==(Vector3 lhs, Vector3 rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
        }

        /// <summary>
        /// Checks for inequality between lhs and rhs
        /// </summary>
        /// <param name="lhs">Vector on the left side of !=</param>
        /// <param name="rhs">Vector on the right side of !=</param>
        /// <returns>True if lhs != rhs</returns>
        public static bool operator !=(Vector3 lhs, Vector3 rhs)
        {
            return !(lhs == rhs);
        }
    }

    /// <summary>
    /// Parameters used to generate levels
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct GenerationParameters
    {
        /// <summary>
        /// Number of nodes that will need to be spawned
        /// </summary>
        public uint count;
        /// <summary>
        /// Size of spawned node
        /// </summary>
        public float size;
        /// <summary>
        /// Position of first spawned node
        /// </summary>
        public Vector3 startPoint;
    }

    /// <summary>
    /// Interface used to represent a node in a sequence
    /// </summary>
    public interface ISequenceNode
    {
        /// <summary>
        /// IEnumerable of possible next nodes
        /// </summary>
        IEnumerable<ISequenceNode> NextNodes { get; }
        /// <summary>
        /// Number of possible next node (Usually NextNodes.Count())
        /// </summary>
        int NextCount { get; }
    }
}
