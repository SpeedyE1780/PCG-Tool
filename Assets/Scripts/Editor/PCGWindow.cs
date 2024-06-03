using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

public class PCGWindow : EditorWindow
{
    [SerializeField]
    private VisualTreeAsset m_VisualTreeAsset = default;

    private ObjectField generatorField;

    [MenuItem("PCG/Open Window")]
    public static void OpenWindow()
    {
        PCGWindow wnd = GetWindow<PCGWindow>();
        wnd.titleContent = new GUIContent("PCG Window");
    }

    public void CreateGUI()
    {
        // Each editor window contains a root VisualElement object
        VisualElement root = rootVisualElement;

        // Instantiate UXML
        VisualElement labelFromUXML = m_VisualTreeAsset.Instantiate();
        root.Add(labelFromUXML);

        var spawnButton = root.Q<Button>("Spawn");
        generatorField = root.Q<ObjectField>("GameObject");

        spawnButton.clicked += SpawnObject;
    }

    private void SpawnObject()
    {
        SimpleGenerator generator = generatorField.value as SimpleGenerator;

        if (generator == null)
        {
            Debug.LogWarning("Generator not set");
            return;
        }

        generator.Generate();
    }
}
