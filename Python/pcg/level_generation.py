from enum import Flag, Enum
from collections.abc import Callable
import ctypes
from pcg import math

pcgDLL = ctypes.CDLL('./pcg-engine-c-api.dll')
    
class ExpansionMode(Enum):
    BFS = 0
    DFS = 1

class Direction(Flag):
    NONE = 0
    LEFT = 1 << 0
    RIGHT = 1 << 1
    FORWARD = 1 << 2
    BACKWARD = 1 << 3
    UP = 1 << 4
    DOWN = 1 << 5
    
class GenerationData(ctypes.Structure):
    _fields_ = [("count", ctypes.c_uint),
                ("size", ctypes.c_float),
                ("startPoint", math.Vector3)]

addNode = ctypes.CFUNCTYPE(ctypes.c_void_p, math.Vector3)
addWFCNode = ctypes.CFUNCTYPE(ctypes.c_void_p, math.Vector3, ctypes.c_int)

def simpleGeneration(generationData : GenerationData, axes : math.Axes, callback : Callable[[math.Vector3], None]) -> None:

    pcgDLL.simpleGeneration(ctypes.pointer(generationData), axes.value, addNode(callback))

def multiDimensionGeneration(generationData : GenerationData, axes : math.Axes, disableOverlap : bool, callback : Callable[[math.Vector3], None]) -> None:
    pcgDLL.multiDimensionGeneration(ctypes.pointer(generationData), axes.value, disableOverlap, addNode(callback))

def waveFunctionCollapseGeneration(generationData : GenerationData, mode : ExpansionMode, axes : math.Axes, callback : Callable[[math.Vector3, Direction], None]) -> None:
    pcgDLL.waveFunctionCollapseGeneration(ctypes.pointer(generationData), mode.value, axes.value, addWFCNode(callback))