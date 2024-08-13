using System.Linq;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    /// <summary>
    /// Class used to generate sequences
    /// </summary>
    public class SequenceGeneration : EditorWindow
    {
        [SerializeField, Tooltip("Sequence Generation Window UXML File")]
        private VisualTreeAsset windowUXML = default;

        private ObjectField startNode;
        private UnsignedIntegerField seedField;
        private TextField fileNameField;
        private TextField folderPathField;
        private ISequenceNode sequenceNode;

        /// <summary>
        /// Adds menu item to Unity Editor to open window
        /// </summary>
        [MenuItem("PCG/Sequence Generation")]
        public static void OpenWindow()
        {
            SequenceGeneration wnd = GetWindow<SequenceGeneration>();
            wnd.titleContent = new GUIContent("Sequence Generation");
        }

        /// <summary>
        /// Called when window is created
        /// </summary>
        public void CreateGUI()
        {
            VisualElement uxmlElements = windowUXML.Instantiate();
            rootVisualElement.Add(uxmlElements);

            startNode = rootVisualElement.Q<ObjectField>("SequenceNode");
            seedField = rootVisualElement.Q<UnsignedIntegerField>("Seed");
            fileNameField = rootVisualElement.Q<TextField>("FileName");
            folderPathField = rootVisualElement.Q<TextField>("FolderPath");
            rootVisualElement.Q<Button>("Generate").clicked += GenerateSequence;

            startNode.RegisterValueChangedCallback(changeEvent => WindowHelper.ValidateObjectField(ref sequenceNode, startNode, changeEvent));
        }

        /// <summary>
        /// Generate Sequence
        /// </summary>
        private void GenerateSequence()
        {
            if (sequenceNode == null)
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
}
