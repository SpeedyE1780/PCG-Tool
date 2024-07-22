using PCGAPI;
using System.Collections.Generic;
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

    void FlattenSequence(ISequenceNode node, int index, List<ISequenceNode> nodes, List<SequenceNode> sequenceNodes)
    {
        SequenceNode current = sequenceNodes[index];
        current.nextCount = node.NextNodes.Count();
        current.nextNodes = new int[current.nextCount];

        for (int i = 0; i < current.nextCount; i++)
        {
            current.nextNodes[i] = nodes.Count;
            ISequenceNode nextNode = node.NextNodes.ElementAt(i);
            nodes.Add(nextNode);
            sequenceNodes.Add(new SequenceNode());
        }

        for (int i = 0; i < current.nextCount; i++)
        {
            int nextIndex = current.nextNodes[i];
            ISequenceNode nextNode = nodes[nextIndex];
            FlattenSequence(nextNode, nextIndex, nodes, sequenceNodes);
        }
    }

    private void GenerateSequence()
    {
        if (startNode.value != null)
        {
            ISequenceNode sequenceNode = (ISequenceNode)startNode.value;
            List<ISequenceNode> nodes = new List<ISequenceNode>() { sequenceNode };
            List<SequenceNode> sequenceNodes = new List<SequenceNode>() { new SequenceNode() };
            FlattenSequence(sequenceNode, 0, nodes, sequenceNodes);
            PCGEngine.GenerateSequence(sequenceNodes[0], index => sequenceNodes[index], index =>
            {
                sequenceNode = nodes[index];
            });
        }
    }
}
