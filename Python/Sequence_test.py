import pytest
from pcg import combinations


class SequenceNode(combinations.SequenceNode):
    def __init__(self, message: str) -> None:
        super().__init__()
        self.message = message

    def generateSequence(self) -> None:
        print(self.message, end="")

        if self.nextNode:
            print("->", end="")
            self.nextNode.generateSequence()
        else:
            print()


def updateSequence(
    currentNode: combinations.SequenceNode,
    sequence: list[combinations.SequenceNode],
    index: int,
):
    if index == -1:
        return 0

    if len(sequence) > 0:
        currentNode = sequence[-1]
    else:
        sequence.append(currentNode)

    currentNode.nextNode = currentNode.nextNodes[index]
    currentNode = currentNode.nextNode
    sequence.append(currentNode)
    return currentNode.nextNodeCount


def test_cyclicSequence(resetSeed):
    red = SequenceNode("Red")
    green = SequenceNode("Green")
    blue = SequenceNode("Blue")
    yellow = SequenceNode("Yellow")
    red.addNextNodes([red, green, blue, yellow])
    green.addNextNodes([red, green, blue, yellow])
    blue.addNextNodes([red, green, blue, yellow])
    yellow.addNextNodes([red, green, blue, yellow])

    currentNode = red
    sequence = []
    expected = [red, blue, yellow, blue, green, yellow, green, green, green, blue]

    combinations.generateCyclicSequence(
        red, 10, lambda index: updateSequence(currentNode, sequence, index)
    )

    assert len(sequence) == 10
    assert expected == sequence
