from enum import Flag

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
    