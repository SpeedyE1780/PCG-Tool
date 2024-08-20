namespace PCGAPI.Tests
{
    public class PCGTest
    {
        public PCGTest()
        {
            PCGEngine.SetSeed(0);
        }

        public static Vector3 ConvertLineToVector3(string line)
        {
            var coordinates = line.Split(' ');
            return new Vector3(float.Parse(coordinates[0]), float.Parse(coordinates[1]), float.Parse(coordinates[2]));
        }

        public static Tuple<Vector3, LevelGenerationDirection> ConvertLineToWFCData(string line)
        {
            var wfcData = line.Split(' ');
            Vector3 position = new(float.Parse(wfcData[0]), float.Parse(wfcData[1]), float.Parse(wfcData[2]));
            LevelGenerationDirection direction = (LevelGenerationDirection)int.Parse(wfcData[3]);
            return new Tuple<Vector3, LevelGenerationDirection>(position, direction);
        }
    }
}
