import ctypes
from collections.abc import Callable

pcgDLL = ctypes.CDLL("./pcg-engine-c-api.dll")

logCallback = ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_char_p)
logFunction = None
"""Function used to log pcg engine messages"""


def setLoggingFunction(callback: Callable[[str], None]):
    """
    Set the function used to log messages from the pcg engine to python

    Args:
        callback (Callable[[str], None]): Function used to log messages
    """

    global logFunction
    logFunction = logCallback(callback)
    pcgDLL.setLoggingFunction(logFunction)
