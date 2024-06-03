using UnityEditor;
using UnityEngine;
using UnityEngine.UIElements;

public class PCGWindow : EditorWindow
{
    [SerializeField]
    private VisualTreeAsset m_VisualTreeAsset = default;

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

        spawnButton.clicked += SpawnObject;
    }

    private void SpawnObject()
    {
        GameObject.CreatePrimitive(PrimitiveType.Cube);
    }
}
