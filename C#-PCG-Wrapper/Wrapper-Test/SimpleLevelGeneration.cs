using System.Collections;

namespace PCGAPI.Tests.LevelGeneration
{
    public class SimpleLevelGeneration : PCGTest
    {
        int index = 0;
        readonly int[] points = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];

        class SimpleLevelGenerationData : IEnumerable<object[]>
        {
            public static readonly Vector3 right = new(1, 0, 0);
            public static readonly Vector3 left = new(-1, 0, 0);
            public static readonly Vector3 up = new(0, 1, 0);
            public static readonly Vector3 down = new(0, -1, 0);
            public static readonly Vector3 forward = new(0, 0, 1);
            public static readonly Vector3 backward = new(0, 0, -1);
            public static readonly Vector3 zero = new(0, 0, 0);

            public IEnumerator<object[]> GetEnumerator()
            {
                yield return new object[] { right };
                yield return new object[] { left };
                yield return new object[] { up };
                yield return new object[] { down };
                yield return new object[] { forward };
                yield return new object[] { backward };
                yield return new object[] { zero };
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return GetEnumerator();
            }
        }

        [Theory]
        [ClassData(typeof(SimpleLevelGenerationData))]
        public void SimpleGeneration(Vector3 offset)
        {
            GenerationParameters parameters = new()
            {
                count = 10,
                size = 1,
            };

            PCGEngine.SimpleGeneration(parameters, offset, position =>
            {
                if (offset == SimpleLevelGenerationData.right)
                {
                    Assert.Equal(points[index], position.x);
                }
                if (offset == SimpleLevelGenerationData.left)
                {
                    Assert.Equal(-points[index], position.x);
                }
                if (offset == SimpleLevelGenerationData.up)
                {
                    Assert.Equal(points[index], position.y);
                }
                if (offset == SimpleLevelGenerationData.down)
                {
                    Assert.Equal(-points[index], position.y);
                }
                if (offset == SimpleLevelGenerationData.forward)
                {
                    Assert.Equal(points[index], position.z);
                }
                if (offset == SimpleLevelGenerationData.backward)
                {
                    Assert.Equal(-points[index], position.z);
                }
                if (offset == SimpleLevelGenerationData.zero)
                {
                    Assert.Equal(0, position.x);
                    Assert.Equal(0, position.y);
                    Assert.Equal(0, position.z);
                }

                index += 1;
            });
        }
    }
}
