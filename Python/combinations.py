import ctypes

pcgDLL = ctypes.CDLL('./pcg-engine-c-apid.dll')

combinationCallback = (ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_int, ctypes.c_bool))

def generateCombination(elementCount, callback):

    pcgDLL.generateCombination(elementCount, combinationCallback(callback))
