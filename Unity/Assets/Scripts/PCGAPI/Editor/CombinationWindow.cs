using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    /// <summary>
    /// Combination Window creates the combination window from the uxml document and allows generating combinations
    /// </summary>
    public class CombinationWindow : EditorWindow
    {
        [SerializeField, Tooltip("Combination Window UXML File")]
        private VisualTreeAsset windowUXML = default;

        private ObjectField combinationObjectField;
        private UnsignedIntegerField seedField;
        private ICombination combination;

        /// <summary>
        /// Adds menu item to Unity Editor to open window
        /// </summary>
        [MenuItem("PCG/Combination Generator")]
        public static void OpenWindow()
        {
            CombinationWindow wnd = GetWindow<CombinationWindow>();
            wnd.titleContent = new GUIContent("Combination Generator");
        }

        /// <summary>
        /// Validate that new object has an ICombination component
        /// </summary>
        /// <param name="changeEvent">Event containing old and new value</param>
        private void ValidateCombinationField(ChangeEvent<Object> changeEvent)
        {
            if (changeEvent.newValue == null)
            {
                return;
            }

            GameObject newGameObject = changeEvent.newValue as GameObject;

            if (newGameObject != null && newGameObject.TryGetComponent(out combination))
            {
                return;
            }

            Debug.LogError($"{newGameObject.name} has no component that inherits from ICombination");
            //this will call the event again
            combinationObjectField.value = changeEvent.previousValue;
        }

        /// <summary>
        /// Called when window is created
        /// </summary>
        public void CreateGUI()
        {
            VisualElement combinationWindow = windowUXML.Instantiate();
            rootVisualElement.Add(combinationWindow);

            combinationObjectField = rootVisualElement.Q<ObjectField>("CombinationObject");
            combinationObjectField.RegisterValueChangedCallback(ValidateCombinationField);

            seedField = rootVisualElement.Q<UnsignedIntegerField>("Seed");

            var generateButton = rootVisualElement.Q<Button>("Generate");
            generateButton.clicked += GenerateCombination;
        }

        /// <summary>
        /// Generate combination using selected seed and object
        /// </summary>
        private void GenerateCombination()
        {
            PCGEngine.SetSeed(seedField.value);
            combination.GenerateCombination();
        }
    }
}
