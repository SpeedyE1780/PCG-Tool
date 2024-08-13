using System.Collections;
using System.Collections.Generic;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    /// <summary>
    /// Collection of helper functions for windows
    /// </summary>
    public static class WindowHelper
    {
        public static void ValidateGameObjectField<T>(ref T component, ObjectField objectField, ChangeEvent<Object> changeEvent)
        {
            if (changeEvent.newValue == null)
            {
                return;
            }

            GameObject newGameObject = changeEvent.newValue as GameObject;

            if (newGameObject != null && newGameObject.TryGetComponent(out component))
            {
                return;
            }

            Debug.LogError($"{newGameObject.name} has no component that inherits from {typeof(T).Name}");
            //this will call the event again
            objectField.value = changeEvent.previousValue;
        }

        public static void ValidateScriptableObjectField<T>(ref T component, ObjectField objectField, ChangeEvent<Object> changeEvent) where T : class
        {
            if (changeEvent.newValue == null)
            {
                return;
            }

            component = changeEvent.newValue as T;

            if (component != null)
            {
                return;
            }

            Debug.LogError($"New value can't be converted to {typeof(T).Name}");
            //this will call the event again
            objectField.value = changeEvent.previousValue;
        }

        /// <summary>
        /// Spawn node in scene
        /// </summary>
        /// <param name="node">Node prefab</param>
        /// <param name="nodeParent">Node parent</param>
        /// <param name="nodePosition">Node world position</param>
        public static void SpawnNode(GameObject node, Transform nodeParent, Vector3 nodePosition)
        {
            UnityEngine.Vector3 position = PCGEngine2Unity.PCGEngineVectorToUnity(nodePosition);
            GameObject n = Object.Instantiate(node, nodeParent);
            n.transform.position = position;
        }

        /// <summary>
        /// Spawn nodes frame by frame
        /// </summary>
        /// <param name="node">Node prefab</param>
        /// <param name="nodeParent">Node parent</param>
        /// <param name="positions">Node world position</param>
        public static IEnumerator GenerateLevel(GameObject node, Transform nodeParent, List<Vector3> positions)
        {
            foreach (Vector3 position in positions)
            {
                if (nodeParent == null)
                {
                    Debug.LogError("Node parent was destroyed ending generation early");
                    yield break;
                }

                SpawnNode(node, nodeParent, position);
                yield return null;
            }
        }
    }
}
