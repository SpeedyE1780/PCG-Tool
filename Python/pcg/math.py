from collections.abc import Callable
import ctypes
from enum import Flag

pcgDLL = ctypes.CDLL("./pcg-engine-c-api.dll")


class Vector3(ctypes.Structure):
    """
    A class representing a 3D vector

    Attributes:
        x (float): The x component of the vector
        y (float): The y component of the vector
        z (float): The z component of the vector
    """

    _fields_ = [("x", ctypes.c_float), ("y", ctypes.c_float), ("z", ctypes.c_float)]

    def __str__(self):
        """
        Return the string representation of the vector in the form of x, y, z

        Returns:
            String representation of the vector in the form of x, y, z
        """
        return "{0}, {1}, {2}".format(self.x, self.y, self.z)


class Axes(Flag):
    """
    Axes represents the 3D axes in 3D space
    """

    NONE = 0
    """Default value representing no axis"""
    POSITIVE_X = 1 << 0
    """+X Axis"""
    NEGATIVE_X = 1 << 1
    """-X Axis"""
    POSITIVE_Y = 1 << 2
    """+Y Axis"""
    NEGATIVE_Y = 1 << 3
    """-Y Axis"""
    POSITIVE_Z = 1 << 4
    """+Z Axis"""
    NEGATIVE_Z = 1 << 5
    """-Z Axis"""
    X = POSITIVE_X | NEGATIVE_X
    """X Axis"""
    Y = POSITIVE_Y | NEGATIVE_Y
    """Y Axis"""
    Z = POSITIVE_Z | NEGATIVE_Z
    """Z Axis"""
    XY = X | Y
    """XY Plane"""
    XZ = X | Z
    """XZ Plane"""
    YZ = Y | Z
    """YZ Plane"""
    XYZ = X | Y | Z
    """XYZ Space"""


seedFunction = None
"""Seed function used to set the RNG seed"""
randomNumberFunction = None
"""Random number generator to generate a number"""

seedCallback = ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_uint)
randomNumberCallback = ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_int, ctypes.c_int)


def setSeed(seed: int) -> None:
    """
    Set the RNG seed

    Args:
        seed (int): RNG seed
    """
    
    pcgDLL.setSeed(seed)


def setRandomGenerator(
    setSeed: Callable[[int], None], randomNumber: Callable[[int, int], int]
) -> None:
    """
    Set RNG seed and random number function

    Args:
        setSeed (Callable[[int], None]): Function used to set the RNG seed
        randomNumber (Callable[[int, int], int]): Function used to generate a random number
    """

    global seedFunction
    global randomNumberFunction

    seedFunction = seedCallback(setSeed)
    randomNumberFunction = randomNumberCallback(randomNumber)

    pcgDLL.setRandomGenerator(seedFunction, randomNumberFunction)
