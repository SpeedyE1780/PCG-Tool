import ctypes
from enum import Flag

class Vector3(ctypes.Structure):
    _fields_  = [("x", ctypes.c_float),
                 ("y", ctypes.c_float),
                 ("z", ctypes.c_float)]
    
    def __str__(self):
        return "{0}, {1}, {2}".format(self.x, self.y, self.z)

class Axes(Flag):
    NONE = 0
    POSITIVE_X = 1 << 0
    NEGATIVE_X = 1 << 1
    POSITIVE_Y = 1 << 2
    NEGATIVE_Y = 1 << 3
    POSITIVE_Z = 1 << 4
    NEGATIVE_Z = 1 << 5
    X = POSITIVE_X | NEGATIVE_X
    Y = POSITIVE_Y | NEGATIVE_Y
    Z = POSITIVE_Z | NEGATIVE_Z
    XY = X | Y
    XZ = X | Z
    YZ = Y | Z
    XYZ = X | Y | Z

seedFunction = None
randomNumberFunction = None
