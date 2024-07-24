from collections.abc import Callable
import ctypes

pcgDLL = ctypes.CDLL('./pcg-engine-c-apid.dll')

combinationCallback = (ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_int, ctypes.c_bool))

def generateCombination(elementCount: int, callback : Callable[[int, bool], None]):

    pcgDLL.generateCombination(elementCount, combinationCallback(callback))

def generateCombinationWithMinimumElements(elementCount :int , minimumElementCount: int, callback : Callable[[int, bool], None]):

    pcgDLL.generateCombinationWithMinimumElementCount(elementCount, minimumElementCount, combinationCallback(callback))

def generateCombinationWithActiveElements(elementCount: int, activeElementsIndex: list[int], activeElementsCount: int, callback: Callable[[int, bool], None]):

    pcgDLL.generateCombinationWithActiveElements(elementCount, (ctypes.c_int * len(activeElementsIndex))(*activeElementsIndex), activeElementsCount, combinationCallback(callback))
