using System.Collections;
using System.Collections.Generic;
using UnityEditor;
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
        /// <summary>
        /// Validate that new value has a component that inherits from T
        /// </summary>
        /// <typeparam name="T">Component base class</typeparam>
        /// <param name="component">Component retrieved from new gameobject</param>
        /// <param name="objectField">ObjectField whose value changed</param>
        /// <param name="changeEvent">Change event</param>
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

        /// <summary>
        /// Validate that new scriptable object inherits from T
        /// </summary>
        /// <typeparam name="T">ScriptableObject derived class</typeparam>
        /// <param name="scriptableObject">ScriptableObject that needs to inherit from T</param>
        /// <param name="objectField">ObjectField whose value changed</param>
        /// <param name="changeEvent">Change event</param>
        public static void ValidateScriptableObjectField<T>(ref T scriptableObject, ObjectField objectField, ChangeEvent<Object> changeEvent) where T : class
        {
            if (changeEvent.newValue == null)
            {
                return;
            }

            scriptableObject = changeEvent.newValue as T;

            if (scriptableObject != null)
            {
                return;
            }

            Debug.LogError($"New value can't be converted to {typeof(T).Name}");
            //this will call the event again
            objectField.value = changeEvent.previousValue;
        }

        /// <summary>
        /// Spawn a gameobject and maintain link in case of prefabs
        /// </summary>
        /// <param name="go">GameObject to spawn</param>
        /// <param name="parent">GameObject parent</param>
        /// <returns>Spawned GameObject linked to prefab in case of prefabs</returns>
        public static GameObject SpawnGameObject(GameObject go, Transform parent)
        {
            GameObject spawnedGameObject = null;

            if (PrefabUtility.IsPartOfAnyPrefab(go))
            {
                spawnedGameObject = PrefabUtility.InstantiatePrefab(go, parent) as GameObject;
            }
            else
            {
                spawnedGameObject = Object.Instantiate(go, parent);
            }

            spawnedGameObject.name = go.name + $"-{parent.childCount}";
            return spawnedGameObject;
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
            GameObject n = SpawnGameObject(node, nodeParent);
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
