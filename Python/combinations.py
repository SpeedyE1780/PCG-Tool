from collections.abc import Callable
import ctypes

pcgDLL = ctypes.CDLL('./pcg-engine-c-api.dll')

combinationCallback = ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_int, ctypes.c_bool)

def generateCombination(elements: list[int], callback : Callable[[int, bool], None]):

    pcgDLL.generateCombination(len(elements), combinationCallback(callback))

def generateCombinationWithMinimumElements(elements : list[int] , minimumElementCount: int, callback : Callable[[int, bool], None]):

    pcgDLL.generateCombinationWithMinimumElementCount(len(elements), minimumElementCount, combinationCallback(callback))

def generateCombinationWithActiveElements(elements: list[int], activeElements : list[int], activeElementsCount: int, callback: Callable[[int, bool], None]):

    activeElementsIndex = []

    for activeElement in activeElements:
        activeElementsIndex.append(elements.index(activeElement))

    pcgDLL.generateCombinationWithActiveElements(len(elements), (ctypes.c_int * len(activeElementsIndex))(*activeElementsIndex), activeElementsCount, combinationCallback(callback))

class SequenceNode:

    def __init__(self) -> None:
        self.nextNodes = []
        self.nextNode = None
        self.nextNodeCount = len(self.nextNodes)

    def addNextNodes(self, nextNodes):
        for node in nextNodes:
            self.nextNodes.append(node)

        self.nextNodeCount = len(self.nextNodes)

updateSequenceCallback = ctypes.CFUNCTYPE(ctypes.c_int, ctypes.c_int)

def getNode(currentNode : SequenceNode , index : int):
    currentNode = currentNode.nextNodes[index]
    return currentNode.node

def generateSequence(sequenceNode : SequenceNode, callback: Callable[[int], None]):
    
    pcgDLL.generateSequence(sequenceNode.nextNodeCount, updateSequenceCallback(callback))
