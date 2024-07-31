namespace PCGAPI
{
    internal class Program
    {
        static void Main(string[] args)
        {
            PCGEngine.GenerateMaze(10, 10, true, MazeAlgorithm.aldousBroder, (x, y, direction) =>
            {
                Console.WriteLine(x + " " + y + " " + direction);
            });
        }
    }
}
