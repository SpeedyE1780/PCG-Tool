using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI
{
    /// <summary>
    /// Generate simple combination
    /// </summary>
    public class SimpleCombination : MonoBehaviour, ICombination
    {
        [SerializeField, Tooltip("List of game object used to generate a combination")]
        private List<GameObject> combinationObjects = new List<GameObject>();

        /// <summary>
        /// Generate a simple combination using combinationObjects
        /// </summary>
        public void GenerateCombination()
        {
            PCGEngine.GenerateCombination(combinationObjects.Count, (index, included) => CombinationHelper.ToggleGameObject(combinationObjects, index, included));
        }
    }
}
