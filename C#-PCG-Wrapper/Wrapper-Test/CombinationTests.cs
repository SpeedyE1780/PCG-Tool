namespace PCGAPI.Tests
{
    public class CombinationTests
    {
        private static void ResetSeed()
        {
            PCGEngine.SetSeed(0);
        }

        private static int[] GetNums()
        {
            return [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
        }

        [Fact]
        public void SimpleCombinations()
        {
            ResetSeed();
            var nums = GetNums();
            List<int> combination = [];
            List<int> expected = new() { 1, 2, 3, 6 };
            PCGEngine.GenerateCombination(nums.Length, (index, included) =>
                {
                    if (included)
                    {
                        combination.Add(nums[index]);
                    }
                });

            Assert.Equal(expected, combination);
        }
    }
}
