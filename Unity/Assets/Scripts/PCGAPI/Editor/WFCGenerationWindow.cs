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

        CommonGenerationFields<WaveFunctionCollapseGenerator, GameObject> generationFields;

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
            generationFields = new CommonGenerationFields<WaveFunctionCollapseGenerator, GameObject>(rootVisualElement, SpawnFunction);
        }

        private GameObject SpawnFunction(Vector3 position)
        {
            GameObject go = null;

            if (PrefabUtility.IsPartOfAnyPrefab(generationFields.Node))
            {
                go = PrefabUtility.InstantiatePrefab(generationFields.Node) as GameObject;
                go.transform.position = position;
            }
            else
            {
                go = Instantiate(generationFields.Node, position, Quaternion.identity);
            }

            Undo.RegisterCreatedObjectUndo(go, "Spawned cell");
            go.transform.SetParent(generationFields.NodeParent);
            return go;
        }
    }
}
