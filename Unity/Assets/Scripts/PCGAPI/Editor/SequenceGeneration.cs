using PCGAPI;
using UnityEditor;
using UnityEngine;
using UnityEngine.UIElements;
using UnityEditor.UIElements;

public class SequenceGeneration : EditorWindow
{
    [SerializeField]
    private VisualTreeAsset m_VisualTreeAsset = default;

    private ObjectField startNode;

    [MenuItem("PCG/Sequence Generation")]
    public static void ShowExample()
    {
        SequenceGeneration wnd = GetWindow<SequenceGeneration>();
        wnd.titleContent = new GUIContent("Sequence Generation");
    }

    public void CreateGUI()
    {
        // Instantiate UXML
        VisualElement uxmlElements = m_VisualTreeAsset.Instantiate();
        rootVisualElement.Add(uxmlElements);

        startNode = rootVisualElement.Q<ObjectField>("SequenceNode");
        rootVisualElement.Q<Button>("Generate").clicked += GenerateSequence;
    }

    private void GenerateSequence()
    {
        if (startNode.value != null)
        {
            ISequenceNode sequenceNode = (ISequenceNode)startNode.value;
            SequenceNode sequence = sequenceNode.ToSequenceNode();
            PCGEngine.GenerateSequence(ref sequence);
        }
    }
}
