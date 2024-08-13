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
    }
}
