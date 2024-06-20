using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI
{
    public class CombinationSet : MonoBehaviour
    {
        [SerializeField]
        private List<GameObject> set = new List<GameObject>();
        [SerializeField]
        private int minimumObjectCount = 0;
        [SerializeField]
        private List<GameObject> includedInSet = new List<GameObject>();

        private void ToggleElement(int index, bool includedInSet)
        {
            set[index].SetActive(includedInSet);
        }

        public void GenerateCombination()
        {
            if (minimumObjectCount == 0 && includedInSet.Count == 0)
            {
                Debug.Log("Calling GenerateCombination with count");
                PCGEngine.GenerateCombination(set.Count, ToggleElement);
            }
            else if (minimumObjectCount > 0 && includedInSet.Count == 0)
            {
                Debug.Log("Calling GenerateCombination with count and minimum");
                PCGEngine.GenerateCombination(set.Count, minimumObjectCount, ToggleElement);
            }
            else if (includedInSet.Count > 0)
            {
                Debug.Log("Calling GenerateCombination with count and included items");
                int[] includedIndices = new int[includedInSet.Count];

                for (int i = 0; i < includedIndices.Length; i++)
                {
                    includedIndices[i] = set.IndexOf(includedInSet[i]);
                }

                PCGEngine.GenerateCombination(set.Count, includedIndices, includedIndices.Length, ToggleElement);
            }
        }
    }
}
