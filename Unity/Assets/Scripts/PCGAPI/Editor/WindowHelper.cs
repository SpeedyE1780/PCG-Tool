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
        public static void ValidateObjectField<T>(ref T component, ObjectField objectField, ChangeEvent<Object> changeEvent)
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

            Debug.LogError($"{newGameObject.name} has no component that inherits from {component}");
            //this will call the event again
            objectField.value = changeEvent.previousValue;
        }
    }
}
