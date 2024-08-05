from collections.abc import Callable
import ctypes
from pcg import math

pcgDLL = ctypes.CDLL('./pcg-engine-c-api.dll')
    
class GenerationData(ctypes.Structure):
    _fields_ = [("count", ctypes.c_uint),
                ("size", ctypes.c_float),
                ("startPoint", math.Vector3)]

addNode = ctypes.CFUNCTYPE(ctypes.c_void_p, math.Vector3)

def simpleGeneration(generationData : GenerationData, axes : math.Axes, callback : Callable[[math.Vector3], None]):

    pcgDLL.simpleGeneration(ctypes.pointer(generationData), axes.value, addNode(callback))

def multiDimensionGeneration(generationData : GenerationData, axes : math.Axes, disableOverlap : bool, callback : Callable[[math.Vector3], None]):
    pcgDLL.multiDimensionGeneration(ctypes.pointer(generationData), axes.value, disableOverlap, addNode(callback))