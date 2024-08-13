using PCGAPI;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

public class SequenceGeneration : EditorWindow
{
    [SerializeField]
    private VisualTreeAsset m_VisualTreeAsset = default;

    private ObjectField startNode;
    private UnsignedIntegerField seedField;
    private TextField fileNameField;
    private TextField folderPathField;

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
        seedField = rootVisualElement.Q<UnsignedIntegerField>("Seed");
        fileNameField = rootVisualElement.Q<TextField>("FileName");
        folderPathField = rootVisualElement.Q<TextField>("FolderPath");
        rootVisualElement.Q<Button>("Generate").clicked += GenerateSequence;
    }

    private void GenerateSequence()
    {
        if (startNode.value == null)
        {
            Debug.LogWarning("Starting node is not set");
            return;
        }

        if (string.IsNullOrWhiteSpace(folderPathField.text))
        {
            Debug.LogWarning("Folder path is not set");
            return;
        }

        if (string.IsNullOrWhiteSpace(fileNameField.text))
        {
            Debug.LogWarning("File name not set");
            return;
        }

        ISequenceNode current = (ISequenceNode)startNode.value;

        SequenceSO sequence = CreateInstance<SequenceSO>();

        PCGEngine.SetSeed(seedField.value);
        PCGEngine.GenerateSequence(current, index =>
        {
            sequence.AddNode(current);

            if (index == -1)
            {
                return 0;
            }

            current = current.NextNodes.ElementAt(index);
            return current.NextCount;
        });

        AssetDatabase.CreateAsset(sequence, $"{folderPathField.text}/{fileNameField.text}{seedField.value}.asset");
        AssetDatabase.SaveAssets();
    }
}
