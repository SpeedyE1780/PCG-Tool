using System.Collections;

namespace PCGAPI.Tests.LevelGeneration
{
    public class SimpleLevelGeneration : PCGTest
    {
        int index = 0;
        readonly int[] points = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];

        class SimpleLevelGenerationData : IEnumerable<object[]>
        {
            public IEnumerator<object[]> GetEnumerator()
            {
                yield return new object[] { Axis.positiveX };
                yield return new object[] { Axis.negativeX };
                yield return new object[] { Axis.positiveY };
                yield return new object[] { Axis.negativeY };
                yield return new object[] { Axis.positiveZ };
                yield return new object[] { Axis.negativeZ };
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return GetEnumerator();
            }
        }

        [Theory]
        [ClassData(typeof(SimpleLevelGenerationData))]
        public void SimpleGeneration(Axis axis)
        {
            GenerationParameters parameters = new()
            {
                count = 10,
                size = 1,
            };

            PCGEngine.SimpleGeneration(ref parameters, axis, position =>
            {
                switch (axis)
                {
                    case Axis.positiveX:
                        {
                            Assert.Equal(points[index], position.x);
                            break;
                        }
                    case Axis.negativeX:
                        {
                            Assert.Equal(-points[index], position.x);
                            break;
                        }
                    case Axis.positiveY:
                        {
                            Assert.Equal(points[index], position.y);
                            break;
                        }
                    case Axis.negativeY:
                        {
                            Assert.Equal(-points[index], position.y);
                            break;
                        }
                    case Axis.positiveZ:
                        {
                            Assert.Equal(points[index], position.z);
                            break;
                        }
                    case Axis.negativeZ:
                        {
                            Assert.Equal(-points[index], position.z);
                            break;
                        }
                }

                index += 1;
            });
        }
    }
}
