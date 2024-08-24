import pytest
from pcg import level_generation, math


@pytest.fixture
def positions():
    return [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]


@pytest.mark.parametrize(
    "axis, positionChecker",
    [
        (math.Vector3(1, 0, 0), lambda position: position.x),
        (math.Vector3(-1, 0, 0), lambda position: -position.x),
        (math.Vector3(0, 1, 0), lambda position: position.y),
        (math.Vector3(0, -1, 0), lambda position: -position.y),
        (math.Vector3(0, 0, 1), lambda position: position.z),
        (math.Vector3(0, 0, -1), lambda position: -position.z),
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
