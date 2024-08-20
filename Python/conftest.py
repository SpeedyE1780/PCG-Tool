import pytest
from pcg import math


@pytest.fixture
def resetSeed():
    math.setSeed(0)
