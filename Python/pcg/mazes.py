from enum import Enum, Flag
from collections.abc import Callable
import ctypes

pcgDLL = ctypes.CDLL("./pcg-engine-c-api.dll")


class NodeValue(Flag):
    """NodeValue represents the if a node has an adjacent node along direction"""

    NONE = 0
    """No adjacent node"""
    LEFT = 1 << 0
    """Adjacent node to the left"""
    RIGHT = 1 << 1
    """Adjacent node to the right"""
    FORWARD = 1 << 2
    """Adjacent node forward"""
    BACKWARD = 1 << 3
    """Adjacent node backward"""


class MazeAlgorithm(Enum):
    """MazeAlgorithm used to generate maze"""

    ALDOUS_BRODER = 0
    """Aldous Broder Algorithm"""
    WILSON = 1
    """Wislon Algorithm"""
    BINARY_TREE_NE = 2
    """Binary Tree Algorithm with north west corridor"""
    BINARY_TREE_NW = 3
    """Binary Tree Algorithm with north east corridor"""
    BINARY_TREE_SE = 4
    """Binary Tree Algorithm with south east corridor"""
    BINARY_TREE_SW = 5
    """Binary Tree Algorithm with south west corridor"""
    SIDEWINDER = 6
    """Sidewinder Algorithm"""
    ELLER = 7
    """Eller Algorithm"""
    HUNT_AND_KILL = 8
    """Hunt and Kill Algorithm"""
    RECURSIVE_BACKTRACKER = 9
    """Recursive Backtracker Algorithm"""
    RECURSIVE_DIVISION = 10
    """Recursive Division Algorithm"""
    KRUSKAL = 11
    """Kruskal Algorithm"""
    PRIM = 12
    """Prim Algorithm"""
    GROWING_TREE_OLDEST = 13
    """Growing Tree Algorithm select oldest pending node"""
    GROWING_TREE_MIDDLE = 14
    """Growing Tree Algorithm select middle pending node"""
    GROWING_TREE_NEWEST = 15
    """Growing Tree Algorithm select newest pending node"""
    GROWING_TREE_RANDOM = 16
    """Growing Tree Algorithm select random pending node"""
    BLOBBY_DIVISION_CORRIDORS = 17
    """Blobby Division Algorithm with no rooms"""
    BLOBBY_DIVISION_SMALL = 18
    """Blobby Division Algorithm with small rooms"""
    BLOBBY_DIVISION_MEDIUM = 19
    """Blobby Division Algorithm with medium rooms"""
    BLOBBY_DIVISION_LARGE = 20
    """Blobby Division Algorithm with large rooms"""
    BLOBBY_DIVISION_HUGE = 21
    """Blobby Division Algorithm with huge rooms"""


mazeCallback = ctypes.CFUNCTYPE(
    ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int
)
growingTreeSelectionCallback = ctypes.CFUNCTYPE(ctypes.c_int, ctypes.c_int)


def generateMaze(
    width: int,
    height: int,
    invokeAfterGeneration: bool,
    algorithm: MazeAlgorithm,
    callback: Callable[[int, int, int], None],
) -> None:
    """
    Generate a maze using the provided algorithm

    Args:
        width (int): Grid Width
        height (int): Grid Height
        invokeAfterGeneration (bool): Wait until level is fully generated to invoke callback or invoke it while level is being generated
        algorithm (MazeAlgorithm): Algorithm used to generate maze
        callback (Callable[[int, int, int], None]): Callback to add node to maze
    """

    pcgDLL.generateMaze(
        width, height, invokeAfterGeneration, algorithm.value, mazeCallback(callback)
    )


def generateGrowingTreeWithCustomSelection(
    width: int,
    height: int,
    invokeAfterGeneration: bool,
    selectionCallback: Callable[[int], int],
    callback: Callable[[int, int, int], None],
) -> None:
    """
    Generate a growing tree maze using a custom selection function

    Args:
        width (int): Grid Width
        height (int): Grid Height
        invokeAfterGeneration (bool): Wait until level is fully generated to invoke callback or invoke it while level is being generated
        selectionCallback (Callable[[int], int]): Callback used to select next pending node
        callback (Callable[[int, int, int], None]): Callback to add node to maze
    """

    pcgDLL.generateGrowingTreeWithCustomSelection(
        width,
        height,
        invokeAfterGeneration,
        growingTreeSelectionCallback(selectionCallback),
        mazeCallback(callback),
    )


def generateBlobbyDivisionWithCustomThreshold(
    width: int,
    height: int,
    invokeAfterGeneration: bool,
    threshold: int,
    callback: Callable[[int, int, int], None],
) -> None:
    """
    Generate a blobby division maze using a custom region threshold

    Args:
        width (int): Grid Width
        height (int): Grid Height
        invokeAfterGeneration (bool): Wait until level is fully generated to invoke callback or invoke it while level is being generated
        threshold (int): Room size threshold
        callback (Callable[[int, int, int], None]): Callback to add node to maze
    """

    pcgDLL.generateBlobbyDivisionWithCustomRegionThreshold(
        width, height, invokeAfterGeneration, threshold, mazeCallback(callback)
    )