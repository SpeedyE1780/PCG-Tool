from enum import Flag, Enum
from collections.abc import Callable
import ctypes
from pcg import math

pcgDLL = ctypes.CDLL("./pcg-engine-c-api.dll")


class ExpansionMode(Enum):
    """
    Expansion Mode decides how will the wave function collapse algorithm process pending nodes
    """

    BFS = 0
    """BFS Expansion will create levels with more connected rooms in a squareish shape"""
    DFS = 1
    """DFS Expansion will create levels with long corridors and some side rooms"""


class Direction(Flag):
    """
    Direction indicates if a node has an adjacent node along the direction
    """

    NONE = 0
    """Node has no adjacent nodes"""
    LEFT = 1 << 0
    """Node has an adjacent node to the left"""
    RIGHT = 1 << 1
    """Node has an adjacent node to the right"""
    FORWARD = 1 << 2
    """Node has an adjacent node forward"""
    BACKWARD = 1 << 3
    """Node has an adjacent node backward"""
    UP = 1 << 4
    """Node has an adjacent node up"""
    DOWN = 1 << 5
    """Node has an adjacent node down"""


class GenerationData(ctypes.Structure):
    """
    A class representing needed data to generate a level

    Attributes:
        count (int): Number of nodes generated
        size (float): Size of node generated
        startPoint (pcg.math.Vector3): Starting position of first node generated
    """

    _fields_ = [
        ("count", ctypes.c_uint),
        ("size", ctypes.c_float),
        ("startPoint", math.Vector3),
    ]


addNode = ctypes.CFUNCTYPE(ctypes.c_void_p, math.Vector3)
addWFCNode = ctypes.CFUNCTYPE(ctypes.c_void_p, math.Vector3, ctypes.c_int)
addGridWFCNode = ctypes.CFUNCTYPE(
    ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int
)
add3DGridWFCNode = ctypes.CFUNCTYPE(
    ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int
)


def simpleGeneration(
    generationData: GenerationData,
    offset: math.Vector3,
    callback: Callable[[math.Vector3], None],
) -> None:
    """
    Generate a level along a single axis

    Args:
        generationData (GenerationData): Data used to generate level
        offset (math.Vector3): Offset between nodes
        callback (Callable[[math.Vector3], None]): Callback used to add node to generated level
    """

    pcgDLL.simpleGeneration(
        ctypes.pointer(generationData), ctypes.pointer(offset), addNode(callback)
    )


def multiDimensionGeneration(
    generationData: GenerationData,
    axes: math.Axes,
    disableOverlap: bool,
    callback: Callable[[math.Vector3], None],
) -> None:
    """
    Generate a level along a multiple axes

    Args:
        generationData (GenerationData): Data used to generate level
        axes (math.Axes): Axes that will be used to generate level
        disableOverlap (bool): Whether or not two nodes can overlap and have the same position
        callback (Callable[[math.Vector3], None]): Callback used to add node to generated level
    """

    pcgDLL.multiDimensionGeneration(
        ctypes.pointer(generationData), axes.value, disableOverlap, addNode(callback)
    )


def waveFunctionCollapseGeneration(
    generationData: GenerationData,
    mode: ExpansionMode,
    axes: math.Axes,
    callback: Callable[[math.Vector3, Direction], None],
) -> None:
    """
    Generate a level using the wave function collapse algorithm

    Args:
        generationData (GenerationData): Data used to generate level
        mode (ExpansionMode): Mode used to process pending nodes
        axes (math.Axes): Axes that will be used to generate level
        callback (Callable[[math.Vector3, Direction], None]): Callback used to add node to generated level
    """

    pcgDLL.waveFunctionCollapseGeneration(
        ctypes.pointer(generationData), mode.value, axes.value, addWFCNode(callback)
    )


def waveFunctionCollapseGridGeneration(
    width: int,
    height: int,
    plane: math.Plane,
    invokeAfterGeneration: bool,
    callback: Callable[[int, int, Direction], None],
) -> None:
    """
    Generate a level using the wave function collapse algorithm in a 2D grid

    Args:
        width (int): Grid width
        height (int): Grid height
        plane (math.Plane): Plane that will be used to generate level
        invokeAfterGeneration (bool): Wait until level is fully generated to invoke callback or invoke it while level is being generated
        callback (Callable[[int, int, Direction], None]): Callback used to add node to generated level
    """

    pcgDLL.waveFunctionCollapseGridGeneration(
        width, height, plane.value, invokeAfterGeneration, addGridWFCNode(callback)
    )


def waveFunctionCollapse3DGridGeneration(
    width: int,
    height: int,
    depth: int,
    invokeAfterGeneration: bool,
    callback: Callable[[int, int, int, Direction], None],
) -> None:
    """
    Generate a level using the wave function collapse algorithm in a 3D grid

    Args:
        width (int): Grid width
        height (int): Grid height
        depth (int): Grid depth
        axes (math.Axes): Axes that will be used to generate level
        invokeAfterGeneration (bool): Wait until level is fully generated to invoke callback or invoke it while level is being generated
        callback (Callable[[int, int, Direction], None]): Callback used to add node to generated level
    """

    pcgDLL.waveFunctionCollapse3DGridGeneration(
        width, height, depth, invokeAfterGeneration, add3DGridWFCNode(callback)
    )