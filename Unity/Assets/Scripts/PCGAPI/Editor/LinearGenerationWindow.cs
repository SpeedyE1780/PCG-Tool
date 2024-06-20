using UnityEditor;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    public class LinearGenerationWindow : EditorWindow
    {
        [SerializeField]
        private VisualTreeAsset m_VisualTreeAsset = default;

        [MenuItem("PCG/Linear Generation")]
        public static void OpenWindow()
        {
            LinearGenerationWindow wnd = GetWindow<LinearGenerationWindow>();
            wnd.titleContent = new GUIContent("Linear Generation");
        }

        public void CreateGUI()
        {
            // Instantiate UXML
            VisualElement uxmlElements = m_VisualTreeAsset.Instantiate();
            rootVisualElement.Add(uxmlElements);
        }

        //private GameObject SpawnFunction(Vector3 position)
        //{
        //    GameObject go = null;

        //    if (PrefabUtility.IsPartOfAnyPrefab(generationFields.Node))
        //    {
        //        go = PrefabUtility.InstantiatePrefab(generationFields.Node) as GameObject;
        //        go.transform.position = position;
        //    }
        //    else
        //    {
        //        go = Instantiate(generationFields.Node, position, Quaternion.identity);
        //    }

        //    Undo.RegisterCreatedObjectUndo(go, "Spawned cell");
        //    go.transform.SetParent(generationFields.NodeParent);
        //    return go;
        //}
    }
}
