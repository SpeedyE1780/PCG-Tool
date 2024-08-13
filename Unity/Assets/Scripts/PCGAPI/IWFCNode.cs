using UnityEngine;

namespace PCGAPI
{
    /// <summary>
    /// IWFCNode is used with level generated using Wave Function Collapse
    /// </summary>
    public interface IWFCNode
    {
        Transform transform { get; }
        GameObject gameObject { get; }

        /// <summary>
        /// Set adjacent Walls/Stairs
        /// </summary>
        /// <param name="adjacentNodes">Adjacent Node Bit Mask</param>
        void SetAdjacentNodes(LevelGenerationDirection adjacentNodes);
    }
}
