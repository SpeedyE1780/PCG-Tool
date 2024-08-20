using System.Collections;

namespace PCGAPI.Tests.LevelGeneration
{
    public class MultiDimensionGeneration : PCGTest
    {
        class MultiDimensionGenerationData : IEnumerable<object[]>
        {
            private readonly List<Axis> skippedValues = [Axis.none, Axis.positiveX, Axis.negativeX, Axis.positiveY, Axis.negativeY, Axis.positiveZ, Axis.negativeZ];

            private static string CheckX(Axis axes)
            {
                if (axes.HasFlag(Axis.positiveX) && axes.HasFlag(Axis.negativeX))
                {
                    return "X";
                }
                else if (axes.HasFlag(Axis.positiveX))
                {
                    return "Px";
                }
                else if (axes.HasFlag(Axis.negativeX))
                {
                    return "Nx";
                }

                return "";
            }

            private static string CheckY(Axis axes)
            {
                if (axes.HasFlag(Axis.positiveY) && axes.HasFlag(Axis.negativeY))
                {
                    return "Y";
                }
                else if (axes.HasFlag(Axis.positiveY))
                {
                    return "Py";
                }
                else if (axes.HasFlag(Axis.negativeY))
                {
                    return "Ny";
                }

                return "";
            }

            private static string CheckZ(Axis axes)
            {
                if (axes.HasFlag(Axis.positiveZ) && axes.HasFlag(Axis.negativeZ))
                {
                    return "Z";
                }
                else if (axes.HasFlag(Axis.positiveZ))
                {
                    return "Pz";
                }
                else if (axes.HasFlag(Axis.negativeZ))
                {
                    return "Nz";
                }

                return "";
            }

            private static string CheckAxes(Axis axes)
            {
                string path = "";
                path += CheckX(axes);
                path += CheckY(axes);
                path += CheckZ(axes);
                return path;
            }

            public IEnumerator<object[]> GetEnumerator()
            {
                for (Axis axes = 0; axes <= Axis.xyz; ++axes)
                {
                    if (skippedValues.Contains(axes))
                    {
                        continue;
                    }

                    string path = CheckAxes(axes) + ".txt";
                    yield return new object[] { axes, path };
                }
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return GetEnumerator();
            }
        }

        private void MultiDimensionGenerationTest(Axis axes, string filePath, bool disableOverlap)
        {
            var positions = File.ReadAllLines(filePath);
            int index = 0;
            GenerationParameters parameters = new GenerationParameters()
            {
                count = 150,
                size = 1,
            };

            PCGEngine.MultiDimensionalGeneration(ref parameters, axes, disableOverlap, position =>
            {
                Vector3 expected = ConvertLineToVector3(positions[index]);
                index++;
                Assert.Equal(expected, position);
            });
        }

        [Theory]
        [ClassData(typeof(MultiDimensionGenerationData))]
        public void MultiDimensionGenerationNoOverlap(Axis axes, string filePath)
        {
            filePath = "GoldenValues/NoOverlap/" + filePath;
            MultiDimensionGenerationTest(axes, filePath, true);
        }

        [Theory]
        [ClassData(typeof(MultiDimensionGenerationData))]
        public void MultiDimensionGenerationOverlap(Axis axes, string filePath)
        {
            filePath = "GoldenValues/Overlap/" + filePath;
            MultiDimensionGenerationTest(axes, filePath, false);
        }
    }
}
