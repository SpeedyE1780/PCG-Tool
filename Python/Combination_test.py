import pytest
from pcg import combinations


@pytest.fixture
def nums():
    return [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]


@pytest.fixture
def combination():
    return []


def test_simpleCombination(resetSeed, nums, combination):
    expected = [1, 2, 3, 6]
    combinations.generateCombination(
        nums,
        lambda index, included: combination.append(nums[index]) if included else None,
    )
    assert expected == combination


def test_combinationWith7Elements(resetSeed, nums, combination):
    expected = [1, 2, 3, 4, 5, 6, 8]
    combinations.generateCombinationWithMinimumElements(
        nums,
        7,
        lambda index, included: combination.append(nums[index]) if included else None,
    )
    assert expected == combination


def test_combinationWith1And3And10Active(resetSeed, nums, combination):
    expected = [1, 2, 3, 6, 10]
    combinations.generateCombinationWithIncludedElements(
        nums,
        [1, 3, 10],
        lambda index, included: combination.append(nums[index]) if included else None,
    )
    assert expected == combination
