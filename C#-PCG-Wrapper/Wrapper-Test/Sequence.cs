namespace PCGAPI.Tests.CombinationGeneration
{
    public class Sequence : PCGTest
    {
        class SequenceNode : ISequenceNode
        {
            public SequenceNode(string name)
            {
                Name = name;
            }

            public SequenceNode(string name, IEnumerable<ISequenceNode> next)
            {
                Name = name;
                AddNodes(next);
            }

            private readonly List<ISequenceNode> nextNodes = [];
            public string Name { get; set; } = "";
            public IEnumerable<ISequenceNode> NextNodes => nextNodes;

            public int NextCount => nextNodes.Count;

            public void AddNodes(IEnumerable<ISequenceNode> next)
            {
                nextNodes.AddRange(next);
            }
        }

        [Fact]
        public void SimpleSequence()
        {
            SequenceNode goldIngots = new("5 Gold Ingots");
            SequenceNode logs = new("10 Logs");
            SequenceNode give = new("Give", [goldIngots, logs]);

            SequenceNode axe = new("Axe");
            SequenceNode dagger = new("Dagger");
            SequenceNode sword = new("Sword");
            SequenceNode craft = new("Craft", [axe, dagger, sword]);

            SequenceNode smith = new("Smith", [give, craft]);

            SequenceNode amulet = new("Amulet of Resistance");
            SequenceNode stolenGold = new("Stolen Gold");
            SequenceNode retrieve = new("Retrieve", [amulet, stolenGold]);

            SequenceNode merchant = new("Merchant", [retrieve]);

            SequenceNode town = new("Town");
            SequenceNode defend = new("Defend", [town]);

            SequenceNode wolf = new("Wolf");
            SequenceNode orc = new("Orc");
            SequenceNode goblin = new("Goblin");
            SequenceNode kill = new("Kill", [wolf, orc, goblin]);

            SequenceNode guildMaster = new("Guild Master", [kill, defend]);

            SequenceNode speak = new("Speak", [guildMaster, merchant, smith]);

            ISequenceNode currentNode = speak;
            List<ISequenceNode> expected = [speak, smith, craft, dagger];
            List<ISequenceNode> sequence = [];

            int UpdateSequence(int index)
            {
                sequence.Add(currentNode);
                if (index == -1)
                {
                    return 0;
                }

                currentNode = currentNode.NextNodes.ElementAt(index);
                return currentNode.NextCount;
            }

            PCGEngine.GenerateSequence(currentNode, UpdateSequence);

            Assert.Equal(expected, sequence);
        }

        [Fact]
        public void CyclicSequence()
        {
            SequenceNode red = new("Red");
            SequenceNode green = new("Green");
            SequenceNode blue = new("Blue");
            SequenceNode yellow = new("Yellow");

            red.AddNodes([red, green, blue, yellow]);
            green.AddNodes([red, green, blue, yellow]);
            blue.AddNodes([red, green, blue, yellow]);
            yellow.AddNodes([red, green, blue, yellow]);

            ISequenceNode currentNode = red;
            List<ISequenceNode> expected = [
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
            ];
            List<ISequenceNode> sequence = [];

            int UpdateSequence(int index)
            {
                sequence.Add(currentNode);
                if (index == -1)
                {
                    return 0;
                }

                currentNode = currentNode.NextNodes.ElementAt(index);
                return currentNode.NextCount;
            }

            PCGEngine.GenerateCyclicSequence(currentNode, 10, UpdateSequence);

            Assert.Equal(expected, sequence);
        }
    }
}
