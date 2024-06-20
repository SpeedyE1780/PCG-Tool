using UnityEditor;
using UnityEngine;
using UnityEngine.UIElements;

namespace PCGAPI.Editor
{
    public class RandomNumberGenerator : EditorWindow
    {
        [SerializeField]
        private VisualTreeAsset m_VisualTreeAsset = default;

        private UnsignedIntegerField seedField;
        private Vector2IntField minMaxField;

        [MenuItem("PCG/Random Number Generator")]
        public static void ShowExample()
        {
            RandomNumberGenerator wnd = GetWindow<RandomNumberGenerator>();
            wnd.titleContent = new GUIContent("Random Number Generator");
        }

        public void CreateGUI()
        {
            // Instantiate UXML
            VisualElement labelFromUXML = m_VisualTreeAsset.Instantiate();
            rootVisualElement.Add(labelFromUXML);

            seedField = rootVisualElement.Q<UnsignedIntegerField>("Seed");
            minMaxField = rootVisualElement.Q<Vector2IntField>("MinMax");

            var generateButton = rootVisualElement.Q<Button>("Generate");

            generateButton.clicked += GenerateRandomNumber;
        }

        private void GenerateRandomNumber()
        {
            static void Log(string message)
            {
                Debug.Log(message);
            }

            static void SetSeed(uint seed)
            {
                Debug.Log("Seed Updated");
                Random.InitState((int)seed);
            }

            static int GenerateNumber(int min, int max)
            {
                return Random.Range(min, max);
            }

            PCGEngine.SetLoggingFunction(Log);
            PCGEngine.SetRandomGenerators(SetSeed, GenerateNumber);

            PCGEngine.SetSeed(seedField.value);

            Debug.Log($"Generated Number: {GenerateNumber(minMaxField.value.x, minMaxField.value.y)}");

            PCGEngine.SetRandomGenerators(null, null);
        }
    }
}
