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


def waveFunctionCollapse4D(mode, filePath):
    file = open(filePath, "r")
    lines = file.readlines()
    index = 0

    def validateFile(position, adjacentNodes):
        nonlocal lines
        nonlocal index

        expectedData = lines[index].strip()
        index += 1
        data = "{0:n} {1:n} {2:n} {3:n} {4}".format(
            position.x, position.y, position.z, position.w, adjacentNodes
        )

        assert data == expectedData

    generationData = level_generation.GenerationData(200, 1, math.Vector3(0, 0, 0))
    level_generation.waveFunctionCollapseGeneration4D(
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


def test_BFS4D(resetSeed):
    waveFunctionCollapse4D(
        level_generation.ExpansionMode.BFS,
        "GoldenValues/WaveFunctionCollapse/4DBFS.txt",
    )


def test_DFS4D(resetSeed):
    waveFunctionCollapse4D(
        level_generation.ExpansionMode.DFS,
        "GoldenValues/WaveFunctionCollapse/4DDFS.txt",
    )
