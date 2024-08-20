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

        public static (Vector3, LevelGenerationDirection) ConvertLineToWFCData(string line)
        {
            var wfcData = line.Split(' ');
            Vector3 position = new(float.Parse(wfcData[0]), float.Parse(wfcData[1]), float.Parse(wfcData[2]));
            LevelGenerationDirection direction = (LevelGenerationDirection)int.Parse(wfcData[3]);
            return (position, direction);
        }

        public static (int, int, LevelGenerationDirection) ConvertLineToWFC2DData(string line)
        {
            var wfcData = line.Split(' ');
            int x = int.Parse(wfcData[0]);
            int y = int.Parse(wfcData[1]);
            LevelGenerationDirection direction = (LevelGenerationDirection)int.Parse(wfcData[2]);
            return (x, y, direction);
        }

        public static (int, int, int, LevelGenerationDirection) ConvertLineToWFC3DData(string line)
        {
            var wfcData = line.Split(' ');
            int x = int.Parse(wfcData[0]);
            int y = int.Parse(wfcData[1]);
            int z = int.Parse(wfcData[2]);
            LevelGenerationDirection direction = (LevelGenerationDirection)int.Parse(wfcData[3]);
            return (x, y, z, direction);
        }

        public static (int, int, MazeDirection) ConvertLineToMazeData(string line)
        {
            var wfcData = line.Split(' ');
            int x = int.Parse(wfcData[0]);
            int y = int.Parse(wfcData[1]);
            MazeDirection direction = (MazeDirection)int.Parse(wfcData[2]);
            return (x, y, direction);
        }
    }
}
