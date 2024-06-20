using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    public class CombinationWindow : EditorWindow
    {
        [SerializeField]
        private VisualTreeAsset m_VisualTreeAsset = default;

        private ObjectField combinationObjectField;
        private UnsignedIntegerField seedField;

        [MenuItem("PCG/Combination Generator")]
        public static void ShowExample()
        {
            CombinationWindow wnd = GetWindow<CombinationWindow>();
            wnd.titleContent = new GUIContent("Combination Generator");
        }

        public void CreateGUI()
        {
            // Instantiate UXML
            VisualElement labelFromUXML = m_VisualTreeAsset.Instantiate();
            rootVisualElement.Add(labelFromUXML);

            combinationObjectField = rootVisualElement.Q<ObjectField>("CombinationObject");
            seedField = rootVisualElement.Q<UnsignedIntegerField>("Seed");

            var generateButton = rootVisualElement.Q<Button>("Generate");
            generateButton.clicked += GenerateCombination;
        }

        private void GenerateCombination()
        {
            PCGEngine.SetSeed(seedField.value);
            CombinationSet set = combinationObjectField.value as CombinationSet;
            set.GenerateCombination();
        }
    }
}
