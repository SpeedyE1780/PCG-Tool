import pytest
from pcg import level_generation, math


def waveFunctionCollapse(mode, filePath):
    file = open(filePath, "r")
    lines = file.readlines()
    index = 0

    def validateFile(position, adjacentNodes):
        nonlocal lines
        nonlocal index

        expectedData = lines[index].strip()
        index += 1
        data = "{0:n} {1:n} {2:n} {3}".format(
            position.x, position.y, position.z, adjacentNodes
        )

        assert data == expectedData

    generationData = level_generation.GenerationData(200, 1, math.Vector3(0, 0, 0))
    level_generation.waveFunctionCollapseGeneration(
        generationData,
        mode,
        math.Axes.XYZ,
        lambda position, adjacentNodes: validateFile(position, adjacentNodes),
    )


def test_BFS(resetSeed):
    waveFunctionCollapse(
        level_generation.ExpansionMode.BFS, "GoldenValues/WaveFunctionCollapse/BFS.txt"
    )


def test_DFS(resetSeed):
    waveFunctionCollapse(
        level_generation.ExpansionMode.DFS, "GoldenValues/WaveFunctionCollapse/DFS.txt"
    )


def test_grid2D(resetSeed):
    file = open("GoldenValues/WaveFunctionCollapse/Grid2D.txt", "r")
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
        10, 10, math.Axes.XZ, False, lambda x, y, adjacent: validateFile(x, y, adjacent)
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
