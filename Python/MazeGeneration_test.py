import pytest
from pcg import mazes


@pytest.fixture
def fileNames():
    return {
        mazes.MazeAlgorithm.ALDOUS_BRODER: "GoldenValues/AldousBroder.txt",
        mazes.MazeAlgorithm.BINARY_TREE_NE: "GoldenValues/BinaryTreeNE.txt",
        mazes.MazeAlgorithm.BINARY_TREE_NW: "GoldenValues/BinaryTreeNW.txt",
        mazes.MazeAlgorithm.BINARY_TREE_SE: "GoldenValues/BinaryTreeSE.txt",
        mazes.MazeAlgorithm.BINARY_TREE_SW: "GoldenValues/BinaryTreeSW.txt",
        mazes.MazeAlgorithm.BLOBBY_DIVISION_CORRIDORS: "GoldenValues/BlobbyDivisionCorridors.txt",
        mazes.MazeAlgorithm.BLOBBY_DIVISION_HUGE: "GoldenValues/BlobbyDivisionHuge.txt",
        mazes.MazeAlgorithm.BLOBBY_DIVISION_LARGE: "GoldenValues/BlobbyDivisionLarge.txt",
        mazes.MazeAlgorithm.BLOBBY_DIVISION_MEDIUM: "GoldenValues/BlobbyDivisionMedium.txt",
        mazes.MazeAlgorithm.BLOBBY_DIVISION_SMALL: "GoldenValues/BlobbyDivisionSmall.txt",
        mazes.MazeAlgorithm.ELLER: "GoldenValues/Eller.txt",
        mazes.MazeAlgorithm.GROWING_TREE_MIDDLE: "GoldenValues/GrowingTreeMiddle.txt",
        mazes.MazeAlgorithm.GROWING_TREE_NEWEST: "GoldenValues/GrowingTreeNewest.txt",
        mazes.MazeAlgorithm.GROWING_TREE_OLDEST: "GoldenValues/GrowingTreeOldest.txt",
        mazes.MazeAlgorithm.GROWING_TREE_RANDOM: "GoldenValues/GrowingTreeRandom.txt",
        mazes.MazeAlgorithm.HUNT_AND_KILL: "GoldenValues/HuntAndKill.txt",
        mazes.MazeAlgorithm.KRUSKAL: "GoldenValues/Kruskal.txt",
        mazes.MazeAlgorithm.PRIM: "GoldenValues/Prim.txt",
        mazes.MazeAlgorithm.RECURSIVE_BACKTRACKER: "GoldenValues/RecursiveBacktracker.txt",
        mazes.MazeAlgorithm.RECURSIVE_DIVISION: "GoldenValues/RecursiveDivision.txt",
        mazes.MazeAlgorithm.SIDEWINDER: "GoldenValues/Sidewinder.txt",
        mazes.MazeAlgorithm.WILSON: "GoldenValues/Wilson.txt",
    }

def getMazeAlgorithms():
    algorithms = []
    for i in range(22):
        algorithms.append(mazes.MazeAlgorithm(i))

    return algorithms


@pytest.mark.parametrize("mazeAlgorithm", getMazeAlgorithms())
def test_mazeGeneration(resetSeed, fileNames, mazeAlgorithm):
    algorithm = mazes.MazeAlgorithm(mazeAlgorithm)
    filePath = fileNames[algorithm]
    file = open(filePath, "r")
    lines = file.readlines()
    index = 0

    def validateFile(x, y, adjacentNodes):
        nonlocal lines
        nonlocal index

        expectedData = lines[index].strip()
        index += 1
        data = "{0} {1} {2}".format(x, y, adjacentNodes)

        assert data == expectedData

    mazes.generateMaze(20, 20, False, algorithm, validateFile)
