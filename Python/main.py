import combinations

def addElement(combination , element, included):
    if included:
        combination.append(element)

def main():
    nums = list(range(0, 16))
    combination = []
    callback = lambda index, included: addElement(combination, nums[index], included)
    print("Generate first combination", end= ' ')

    combinations.generateCombination(nums, callback)
    print(combination)

    combination = []
    print("Generate combination with at least 7 elements", end= ' ')
    combinations.generateCombinationWithMinimumElements(nums, 7, callback)
    print(combination)

    combination = []
    print("Generate combination with element 2, 3, 5 active", end= ' ')
    combinations.generateCombinationWithActiveElements(nums, [2, 3, 5], 3, callback)
    print(combination)

main()
