using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI.Demo
{
    /// <summary>
    /// Generate a combination that must include selected elements
    /// </summary>
    public class IncludedCombination : MonoBehaviour, ICombination
    {
        [SerializeField, Tooltip("List of game object used to generate a combination")]
        private List<GameObject> combinationObjects = new List<GameObject>();
        [SerializeField, Tooltip("List of game object included in generated combination")]
        private List<GameObject> includedInCombination = new List<GameObject>();

        /// <summary>
        /// Generate a combination that includes all gameobjects in includedInCombination
        /// </summary>
        public void GenerateCombination()
        {
            int[] includedIndices = new int[includedInCombination.Count];

            for (int i = 0; i < includedIndices.Length; i++)
            {
                includedIndices[i] = combinationObjects.IndexOf(includedInCombination[i]);
            }

            PCGEngine.GenerateCombination(combinationObjects.Count, includedIndices, includedIndices.Length, (index, included) => CombinationHelper.ToggleGameObject(combinationObjects, index, included));
        }
    }
}
