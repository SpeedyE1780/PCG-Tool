from collections.abc import Callable
import ctypes

pcgDLL = ctypes.CDLL("./pcg-engine-c-api.dll")

combinationCallback = ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_int, ctypes.c_bool)


def generateCombination(elements: list, callback: Callable[[int, bool], None]) -> None:
    """
    Generate a combination from a list of elements

    Args:
        elements (list): List containing all possible elements in combination
        callback (Callable[[int, bool], None]): Callback to indicate if element is included or no
    """
    pcgDLL.generateCombination(len(elements), combinationCallback(callback))


def generateCombinationWithMinimumElements(
    elements: list, minimumElementCount: int, callback: Callable[[int, bool], None]
) -> None:
    """
    Generate a combination from a list of elements with at least minimumElementCount active

    Args:
        elements (list): List containing all possible elements in combination
        minimumElementCount (int): Minimum count of elements in combination
        callback (Callable[[int, bool], None]): Callback to indicate if element is included or no
    """
    pcgDLL.generateCombinationWithMinimumElementCount(
        len(elements), minimumElementCount, combinationCallback(callback)
    )


def generateCombinationWithIncludedElements(
    elements: list,
    includedElements: list,
    callback: Callable[[int, bool], None],
) -> None:
    """
    Generate a combination from a list of elements with the passed in elements included

    Args:
        elements (list): List containing all possible elements in combination
        includedElements (list): List of elements that will be included in combination
        callback (Callable[[int, bool], None]): Callback to indicate if element is included or no
    """
    includedElementsIndex = []

    for activeElement in includedElements:
        includedElementsIndex.append(elements.index(activeElement))

    pcgDLL.generateCombinationWithActiveElements(
        len(elements),
        (ctypes.c_int * len(includedElementsIndex))(*includedElementsIndex),
        len(includedElementsIndex),
        combinationCallback(callback),
    )


class SequenceNode:
    """
    A class representing a node in a sequence

    Attributes:
        nextNodes (list[SequenceNode]): List of possible nodes after this node
        nextNode (SequenceNode): Node after this node in sequence
        nextNodeCount (int): len of nextNodes
    """

    def __init__(self) -> None:
        """
        Initialize an empty Sequence Node
        """
        self.nextNodes = []
        self.nextNode = None
        self.nextNodeCount = len(self.nextNodes)

    def addNextNodes(self, nextNodes: list):
        """
        Add possible next nodes to node

        Args:
            nextNodes (list[SequenceNode]): List of possible nodes after this node in sequence
        """
        for node in nextNodes:
            self.nextNodes.append(node)

        self.nextNodeCount = len(self.nextNodes)


updateSequenceCallback = ctypes.CFUNCTYPE(ctypes.c_int, ctypes.c_int)


def generateSequence(
    sequenceNode: SequenceNode, callback: Callable[[int], int]
) -> None:
    """
    Generate a sequence starting with sequenceNode

    Args:
        sequenceNode (SequenceNode): Starting node in sequence
        callback (Callable[[int], int]): Callback to set next node in sequence and returns the possible next node count
    """
    pcgDLL.generateSequence(
        sequenceNode.nextNodeCount, updateSequenceCallback(callback)
    )
