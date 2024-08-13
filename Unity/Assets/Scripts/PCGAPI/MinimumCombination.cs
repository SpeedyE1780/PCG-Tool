using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI
{
    /// <summary>
    /// Generates a combination using a list of GameObject and a minimum count of element
    /// </summary>
    public class MinimumCombination : MonoBehaviour, ICombination
    {
        [SerializeField, Tooltip("List of game object used to generate a combination")]
        private List<GameObject> combinationObjects = new List<GameObject>();
        [SerializeField, Tooltip("Minimum count in generated combination")]
        private int count;

        /// <summary>
        /// Generate a combination using at least count of combinationObjects
        /// </summary>
        public void GenerateCombination()
        {
            PCGEngine.GenerateCombination(combinationObjects.Count, count, (index, included) => CombinationHelper.ToggleGameObject(combinationObjects, index, included));
        }
    }
}
