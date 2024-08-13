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
        private Toggle cyclicToggle;
        private UnsignedIntegerField sequenceLengthField;
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
        /// Show/hide sequence length when generating cyclic/non cyclic sequences
        /// </summary>
        /// <param name="visible">If field should be visible</param>
        private void UpdateSequenceLengthDisplay(bool visible)
        {
            sequenceLengthField.style.display = visible ? DisplayStyle.Flex : DisplayStyle.None;
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
            cyclicToggle = rootVisualElement.Q<Toggle>("CyclicToggle");
            sequenceLengthField = rootVisualElement.Q<UnsignedIntegerField>("SequenceLength");

            cyclicToggle.RegisterValueChangedCallback(changeEvent => UpdateSequenceLengthDisplay(changeEvent.newValue));
            UpdateSequenceLengthDisplay(cyclicToggle.value);


            rootVisualElement.Q<Button>("Generate").clicked += GenerateSequence;
            startNode.RegisterValueChangedCallback(changeEvent => WindowHelper.ValidateScriptableObjectField(ref sequenceNode, startNode, changeEvent));
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

            if (cyclicToggle.value && sequenceLengthField.value == 0)
            {
                Debug.LogWarning("Sequence length must be greater than zero when generating cyclic sequence");
                return;
            }

            ISequenceNode current = (ISequenceNode)startNode.value;

            SequenceSO sequence = CreateInstance<SequenceSO>();

            PCGEngine.SetSeed(seedField.value);

            UpdateSequence callback = index =>
            {
                sequence.AddNode(current);

                if (index == -1)
                {
                    return 0;
                }

                current = current.NextNodes.ElementAt(index);
                return current.NextCount;
            };

            if (cyclicToggle.value)
            {
                PCGEngine.GenerateCyclicSequence(current, (int)sequenceLengthField.value, callback);
            }
            else
            {
                PCGEngine.GenerateSequence(current, callback);
            }

            AssetDatabase.CreateAsset(sequence, $"{folderPathField.text}/{fileNameField.text}{seedField.value}.asset");
            AssetDatabase.SaveAssets();
        }
    }
}
