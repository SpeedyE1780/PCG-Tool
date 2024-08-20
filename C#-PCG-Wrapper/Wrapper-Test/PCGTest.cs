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
    }
}
