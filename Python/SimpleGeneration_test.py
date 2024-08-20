import pytest
from pcg import level_generation, math


@pytest.fixture
def positions():
    return [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]


@pytest.mark.parametrize(
    "axis, positionChecker",
    [
        (math.Axes.POSITIVE_X, lambda position: position.x),
        (math.Axes.NEGATIVE_X, lambda position: -position.x),
        (math.Axes.POSITIVE_Y, lambda position: position.y),
        (math.Axes.NEGATIVE_Y, lambda position: -position.y),
        (math.Axes.POSITIVE_Z, lambda position: position.z),
        (math.Axes.NEGATIVE_Z, lambda position: -position.z),
    ],
)
def test_simpleLevelGeneration(resetSeed, positions, axis, positionChecker):
    generationData = level_generation.GenerationData(10, 1, math.Vector3(0, 0, 0))
    index = 0

    def callback(position):
        nonlocal index
        assert positions[index] == positionChecker(position)
        index += 1

    level_generation.simpleGeneration(
        generationData, axis, lambda position: callback(position)
    )
