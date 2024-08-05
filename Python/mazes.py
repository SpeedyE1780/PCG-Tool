from enum import Enum, Flag
from collections.abc import Callable
import ctypes

pcgDLL = ctypes.CDLL('./pcg-engine-c-api.dll')

class NodeValue(Flag):
    none = 0
    LEFT = 1 << 0
    RIGHT = 1 << 1
    FORWARD = 1 << 2
    BACKWARD = 1 << 3

class MazeAlgorithm(Enum):
    ALDOUS_BRODER = 0
    WILSON = 1
    BINARY_TREE_NE = 2
    BINARY_TREE_NW = 3
    BINARY_TREE_SE = 4
    BINARY_TREE_SW = 5
    SIDEWINDER = 6
    ELLER = 7
    HUNT_AND_KILL = 8
    RECURSIVE_BACKTRACKER = 9
    RECURSIVE_DIVISION = 10
    KRUSKAL = 11
    PRIM = 12
    GROWING_TREE_OLDEST = 13
    GROWING_TREE_MIDDLE = 14
    GROWING_TREE_NEWEST = 15
    GROWING_TREE_RANDOM = 16
    BLOBBY_DIVISION_CORRIDORS = 17
    BLOBBY_DIVISION_SMALL = 18
    BLOBBY_DIVISION_MEDIUM = 19
    BLOBBY_DIVISION_LARGE = 20
    BLOBBY_DIVISION_HUGE = 21

mazeCallback = ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int)