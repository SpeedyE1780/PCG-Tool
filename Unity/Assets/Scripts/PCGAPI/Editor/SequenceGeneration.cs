using PCGAPI;
using UnityEditor;
using UnityEngine;
using UnityEngine.UIElements;

public class SequenceGeneration : EditorWindow
{
    [SerializeField]
    private VisualTreeAsset m_VisualTreeAsset = default;

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

        rootVisualElement.Q<Button>("Generate").clicked += GenerateSequence;
    }

    unsafe private void GenerateSequence()
    {
        SequenceNode gold = new SequenceNode()
        {
            nextCount = 0,
            nextNode = null,
            nextNodes = null
        };

        SequenceNode logs = new SequenceNode()
        {
            nextCount = 0,
            nextNode = null,
            nextNodes = null
        };

        SequenceNode[] goldLogs = new SequenceNode[2] { gold, logs };

        fixed (SequenceNode* glPtr = goldLogs)
        {
            SequenceNode give = new SequenceNode()
            {
                nextCount = 2,
                nextNode = null,
                nextNodes = glPtr
            };

            PCGEngine.GenerateSequence(ref give);

            Debug.Log(give.nextNode == null);
        }
    }
}
