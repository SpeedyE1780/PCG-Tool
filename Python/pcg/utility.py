import ctypes
from collections.abc import Callable

pcgDLL = ctypes.CDLL('./pcg-engine-c-api.dll')

logCallback = ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_char_p)
logFunction = None

def setLoggingFunction(callback : Callable[[str], None]):
    global logFunction
    logFunction = logCallback(callback)
    pcgDLL.setLoggingFunction(logFunction)
