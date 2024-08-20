import pytest
from pcg import level_generation, math


def checkXAxis(axes: math.Axes):
    if bool(axes & math.Axes.POSITIVE_X) and bool(axes & math.Axes.NEGATIVE_X):
        return "X"
    elif bool(axes & math.Axes.POSITIVE_X):
        return "Px"
    elif bool(axes & math.Axes.NEGATIVE_X):
        return "Nx"
    else:
        return ""


def checkYAxis(axes: math.Axes):
    if bool(axes & math.Axes.POSITIVE_Y) and bool(axes & math.Axes.NEGATIVE_Y):
        return "Y"
    elif bool(axes & math.Axes.POSITIVE_Y):
        return "Py"
    elif bool(axes & math.Axes.NEGATIVE_Y):
        return "Ny"
    else:
        return ""


def checkZAxis(axes: math.Axes):
    if bool(axes & math.Axes.POSITIVE_Z) and bool(axes & math.Axes.NEGATIVE_Z):
        return "Z"
    elif bool(axes & math.Axes.POSITIVE_Z):
        return "Pz"
    elif bool(axes & math.Axes.NEGATIVE_Z):
        return "Nz"
    else:
        return ""


def getFileName(axes: math.Axes):
    path = checkXAxis(axes)
    path += checkYAxis(axes)
    path += checkZAxis(axes)
    return path


def getAllAxes():

    axesPair = []
    skippedValues = [
        math.Axes.NONE,
        math.Axes.POSITIVE_X,
        math.Axes.NEGATIVE_X,
        math.Axes.POSITIVE_Y,
        math.Axes.NEGATIVE_Y,
        math.Axes.POSITIVE_Z,
        math.Axes.NEGATIVE_Z,
    ]

    for i in range(math.Axes.XYZ.value + 1):
        axes = math.Axes(i)

        if axes in skippedValues:
            continue

        axesPair.append((axes, getFileName(axes)))

    return axesPair


def multiDimensionGeneration(axes, filePath, disableOverlap):
    file = open(filePath, "r")
    lines = file.readlines()
    index = 0

    def validateFile(position):
        nonlocal lines
        nonlocal index

        expectedData = lines[index].strip()
        index += 1
        data = "{0:n} {1:n} {2:n}".format(position.x, position.y, position.z)

        assert data == expectedData

    generationData = level_generation.GenerationData(150, 1, math.Vector3(0, 0, 0))
    level_generation.multiDimensionGeneration(
        generationData, axes, disableOverlap, lambda position: validateFile(position)
    )


@pytest.mark.parametrize("axes, fileName", getAllAxes())
def test_multiDimensionGenerationNoOverlap(resetSeed, axes, fileName):
    filePath = "GoldenValues/NoOverlap/{0}.txt".format(fileName)
    multiDimensionGeneration(axes, filePath, True)


@pytest.mark.parametrize("axes, fileName", getAllAxes())
def test_multiDimensionGenerationOverlap(resetSeed, axes, fileName):
    filePath = "GoldenValues/Overlap/{0}.txt".format(fileName)
    multiDimensionGeneration(axes, filePath, False)
