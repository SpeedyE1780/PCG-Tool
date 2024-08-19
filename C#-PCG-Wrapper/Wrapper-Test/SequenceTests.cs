
namespace PCGAPI.Tests
{
    public class SequenceTests
    {
        class SequenceNode : ISequenceNode
        {
            public SequenceNode(string name)
            {
                Name = name;
            }

            private readonly List<ISequenceNode> nextNodes = [];
            public string Name { get; set; } = "";
            public IEnumerable<ISequenceNode> NextNodes => nextNodes;

            public int NextCount => nextNodes.Count;

            public void AddNode(IEnumerable<ISequenceNode> node)
            {
                nextNodes.AddRange(node);
            }

        }

        [Fact]
        public void CyclicSequence()
        {
            PCGEngine.SetSeed(0);
            SequenceNode red = new("Red");
            SequenceNode green = new("Green");
            SequenceNode blue = new("Blue");
            SequenceNode yellow = new("Yellow");

            red.AddNode([red, green, blue, yellow]);
            green.AddNode([red, green, blue, yellow]);
            blue.AddNode([red, green, blue, yellow]);
            yellow.AddNode([red, green, blue, yellow]);

            ISequenceNode currentNode = red;
            List<ISequenceNode> expected = new List<ISequenceNode> {
                red,
                blue,
                yellow,
                blue,
                green,
                yellow,
                green,
                green,
                green,
                blue
            };
            List<ISequenceNode> sequence = new List<ISequenceNode>();

            UpdateSequence updateSequence = index =>
            {
                sequence.Add(currentNode);
                if (index == -1)
                {
                    return 0;
                }

                currentNode = currentNode.NextNodes.ElementAt(index);
                return currentNode.NextCount;
            };

            PCGEngine.GenerateCyclicSequence(currentNode, 10, updateSequence);

            Assert.Equal(expected, sequence);
        }
    }
}
