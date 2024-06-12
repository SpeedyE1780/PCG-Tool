using PCGAPI.Generators;
using UnityEditor;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    public class WFCGenerationWindow : EditorWindow
    {
        [SerializeField]
        private VisualTreeAsset m_VisualTreeAsset = default;

        CommonGenerationFields<WaveFunctionCollapseGenerator, WFCNode> generationFields;

        [MenuItem("PCG/Wave Function Colapse Generation")]
        public static void OpenWindow()
        {
            WFCGenerationWindow wnd = GetWindow<WFCGenerationWindow>();
            wnd.titleContent = new GUIContent("Wave Function Colapse Generation");
        }

        public void CreateGUI()
        {
            // Instantiate UXML
            VisualElement uxmlElements = m_VisualTreeAsset.Instantiate();
            rootVisualElement.Add(uxmlElements);
            generationFields = new CommonGenerationFields<WaveFunctionCollapseGenerator, WFCNode>(rootVisualElement, SpawnFunction);
        }

        private WFCNode SpawnFunction(Vector3 position)
        {
            WFCNode node = null;

            if (PrefabUtility.IsPartOfAnyPrefab(generationFields.Node))
            {
                node = PrefabUtility.InstantiatePrefab(generationFields.Node) as WFCNode;
                node.transform.position = position;
            }
            else
            {
                node = Instantiate(generationFields.Node, position, Quaternion.identity);
            }

            Undo.RegisterCreatedObjectUndo(node, "Spawned cell");
            node.transform.SetParent(generationFields.NodeParent);
            return node;
        }
    }
}
