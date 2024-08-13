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
        /// Called when window is created
        /// </summary>
        public void CreateGUI()
        {
            VisualElement combinationWindow = windowUXML.Instantiate();
            rootVisualElement.Add(combinationWindow);

            combinationObjectField = rootVisualElement.Q<ObjectField>("CombinationObject");
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
            CombinationSet set = combinationObjectField.value as CombinationSet;
            set.GenerateCombination();
        }
    }
}
