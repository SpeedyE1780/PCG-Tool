import combinations

def addElement(combination , element, included):
    if included:
        combination.append(element)

def main():
    nums = list(range(0, 16))
    combination = []
    combinations.generateCombination(len(nums), lambda index, included: addElement(combination, nums[index], included))
    print(combination)

main()
