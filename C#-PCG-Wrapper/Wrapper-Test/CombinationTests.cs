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

        [Fact]
        public void CombinationWith7Elements()
        {
            ResetSeed();
            var nums = GetNums();
            List<int> combination = [];
            List<int> expected = new() { 1, 2, 3, 4, 5, 6, 8 };
            PCGEngine.GenerateCombination(nums.Length, 7, (index, included) =>
                {
                    if (included)
                    {
                        combination.Add(nums[index]);
                    }
                });

            Assert.Equal(expected, combination);
        }

        [Fact]
        public void CombinationWith1And3And10Active()
        {
            ResetSeed();
            var nums = GetNums();
            List<int> combination = [];
            List<int> expected = new() { 1, 2, 3, 6, 10 };
            PCGEngine.GenerateCombination(nums.Length, [0, 2, 9], 3, (index, included) =>
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
