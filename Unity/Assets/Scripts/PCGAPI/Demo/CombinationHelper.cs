using System.Collections.Generic;
using UnityEngine;

namespace PCGAPI.Demo
{
    /// <summary>
    /// CombinationHelper contains common function used in all type of combinations
    /// </summary>
    public static class CombinationHelper
    {
        /// <summary>
        /// Set a gameobject active or not
        /// </summary>
        /// <param name="gameObjects">List of gameObjects used to generate combination</param>
        /// <param name="index">Current gameobject index</param>
        /// <param name="active">If gameobject is active or not</param>
        public static void ToggleGameObject(List<GameObject> gameObjects, int index, bool active)
        {
            gameObjects[index].SetActive(active);
        }
    }
}
