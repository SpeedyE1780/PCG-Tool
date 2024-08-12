﻿// See https://aka.ms/new-console-template for more information
using PCGAPI;

PCGEngine.GenerateMaze(10, 10, true, MazeAlgorithm.aldousBroder, (x, y, direction) =>
{
    Console.WriteLine(x + " " + y + " " + direction);
});

DemoSequenceNode node1 = new()
{
    Name = "node 1"
};
DemoSequenceNode node2 = new()
{
    Name = "node 2"
};
node1.AddNode(node2);
DemoSequenceNode node3 = new()
{
    Name = "node 3"
};
DemoSequenceNode node4 = new()
{
    Name = "node 4"
};
node2.AddNode(node3);
node2.AddNode(node4);
DemoSequenceNode node5 = new()
{
    Name = "node 5"
};
node4.AddNode(node5);

ISequenceNode currentNode = node1;

Console.WriteLine("Genereate Sequence");
PCGEngine.GenerateSequence(currentNode, index =>
{
    Console.WriteLine(((DemoSequenceNode)currentNode).Name);

    if (index == -1)
    {
        return 0;
    }

    currentNode = currentNode.NextNodes.ElementAt(index);
    return currentNode.NextCount;
});

Console.WriteLine("Generate combination with 15 elements");
PCGEngine.GenerateCombination(15, (index, active) =>
{
    if (active)
    {
        Console.WriteLine(index + 1);
    }
});

internal class DemoSequenceNode : ISequenceNode
{
    private readonly List<ISequenceNode> children = [];

    public string Name { get; set; } = "";
    public IEnumerable<ISequenceNode> NextNodes => children;
    public int NextCount => children.Count;

    public void AddNode(ISequenceNode node)
    {
        children.Add(node);
    }
}
