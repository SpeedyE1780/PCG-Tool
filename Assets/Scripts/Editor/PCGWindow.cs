using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

public class PCGWindow : EditorWindow
{
    [SerializeField]
    private VisualTreeAsset m_VisualTreeAsset = default;

    private ObjectField generatorField;
    private ObjectField cellField;
    private IntegerField seedField;
    private UnsignedIntegerField cellLimitField;
    private FloatField cellSizeField;
    private Vector3Field startPositionField;

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

        generatorField = root.Q<ObjectField>("Generator");
        cellField = root.Q<ObjectField>("Cell");
        seedField = root.Q<IntegerField>("Seed");
        cellLimitField = root.Q<UnsignedIntegerField>("CellLimit");
        cellSizeField = root.Q<FloatField>("CellSize");
        startPositionField = root.Q<Vector3Field>("StartPosition");

        var generateButton = root.Q<Button>("GenerateButton");
        generateButton.clicked += SpawnObject;
    }

    private void SpawnObject()
    {
        Generator generator = generatorField.value as Generator;
        GameObject cell = cellField.value as GameObject;
        int seed = seedField.value;
        uint limit = cellLimitField.value;
        float size = cellSizeField.value;
        Vector3 startPosition = startPositionField.value;

        if (generator == null)
        {
            Debug.LogWarning("Generator not set");
            return;
        }

        if (cell == null)
        {
            Debug.LogWarning("Cell not set");
            return;
        }

        if (limit == 0)
        {
            Debug.LogWarning("Limit is zero nothing to generate");
            return;
        }

        if (size == 0)
        {
            Debug.LogWarning("Cell size is 0 object will spawn on top of one another");
            return;
        }

        Random.InitState(seed);
        generator.Generate(new GeneratorData(cell, limit, size, startPosition));
    }
}
