import pytest
from pcg import level_generation, math


@pytest.mark.parametrize(
    "plane, fileName",
    [
        (math.Plane.XY, "Grid2DXY"),
        (math.Plane.XZ, "Grid2DXZ"),
        (math.Plane.YZ, "Grid2DYZ"),
    ],
)
def test_grid2D(resetSeed, plane, fileName):
    file = open("GoldenValues/WaveFunctionCollapse/{}.txt".format(fileName), "r")
    lines = file.readlines()
    index = 0

    def validateFile(x, y, adjacentNodes):
        nonlocal lines
        nonlocal index

        expectedData = lines[index].strip()
        index += 1
        data = "{0} {1} {2}".format(x, y, adjacentNodes)

        assert data == expectedData

    level_generation.waveFunctionCollapseGridGeneration(
        10,
        10,
        plane,
        False,
        lambda x, y, adjacent: validateFile(x, y, adjacent),
    )


def test_grid3D(resetSeed):
    file = open("GoldenValues/WaveFunctionCollapse/Grid3D.txt", "r")
    lines = file.readlines()
    index = 0

    def validateFile(x, y, z, adjacentNodes):
        nonlocal lines
        nonlocal index

        expectedData = lines[index].strip()
        index += 1
        data = "{0} {1} {2} {3}".format(x, y, z, adjacentNodes)

        assert data == expectedData

    level_generation.waveFunctionCollapse3DGridGeneration(
        10, 10, 10, False, lambda x, y, z, adjacent: validateFile(x, y, z, adjacent)
    )
