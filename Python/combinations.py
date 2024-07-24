from collections.abc import Callable
import ctypes

pcgDLL = ctypes.CDLL('./pcg-engine-c-apid.dll')

combinationCallback = (ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_int, ctypes.c_bool))

def generateCombination(elements: list[int], callback : Callable[[int, bool], None]):

    pcgDLL.generateCombination(len(elements), combinationCallback(callback))

def generateCombinationWithMinimumElements(elements : list[int] , minimumElementCount: int, callback : Callable[[int, bool], None]):

    pcgDLL.generateCombinationWithMinimumElementCount(len(elements), minimumElementCount, combinationCallback(callback))

def generateCombinationWithActiveElements(elements: list[int], activeElements : list[int], activeElementsCount: int, callback: Callable[[int, bool], None]):

    activeElementsIndex = []

    for activeElement in activeElements:
        activeElementsIndex.append(elements.index(activeElement))

    pcgDLL.generateCombinationWithActiveElements(len(elements), (ctypes.c_int * len(activeElementsIndex))(*activeElementsIndex), activeElementsCount, combinationCallback(callback))
