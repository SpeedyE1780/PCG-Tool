from pcg import combinations, mazes, level_generation, math

class QuestSequence(combinations.SequenceNode):

    def __init__(self, message : str) -> None:
        super().__init__()
        self.message = message

    def generateSequence(self) -> None:

        print(self.message, end='')

        if(self.nextNode):
            print('->', end='')
            self.nextNode.generateSequence()
        else:
            print()

def addElement(combination , element, included) -> None:
    if included:
        combination.append(element)

def combinationsDemo() -> None :

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

    gold = QuestSequence("5 Gold Ingots")
    logs = QuestSequence("10 Logs")

    give = QuestSequence("Give")
    give.addNextNodes([gold, logs])

    axe = QuestSequence("Axe")
    dagger = QuestSequence("Dagger")
    sword = QuestSequence("Sword")

    craft = QuestSequence("Craft")
    craft.addNextNodes([axe, dagger, sword])

    smith = QuestSequence("Smith")
    smith.addNextNodes([craft, give])

    stolenGold = QuestSequence("Stolen Gold")
    amulet = QuestSequence("Amulet of Resistance")

    retrieve = QuestSequence("Retrieve")
    retrieve.addNextNodes([stolenGold, amulet])

    merchant = QuestSequence("Merchant")
    merchant.addNextNodes([retrieve])

    town = QuestSequence("Town")
    defend = QuestSequence("Defend")
    defend.addNextNodes([town])

    wolf = QuestSequence("Wolf")
    orc = QuestSequence("Orc")
    goblin = QuestSequence("Goblin")
    kill = QuestSequence("Kill")
    kill.addNextNodes([wolf, orc, goblin])

    guildMaster = QuestSequence("Guild Master")
    guildMaster.addNextNodes([kill, defend])

    speak = QuestSequence("Speak")
    speak.addNextNodes([guildMaster, merchant, smith])

    currentNode = speak
    sequence = []
    
    def updateSequence(currentNode: combinations.SequenceNode, sequence : list[combinations.SequenceNode], index : int):

            if index == -1:
                return 0
            
            if(len(sequence) > 0):
                currentNode = sequence[-1]
            
            currentNode.nextNode = currentNode.nextNodes[index]
            currentNode = currentNode.nextNode
            sequence.append(currentNode)
            return currentNode.nextNodeCount

    combinations.generateSequence(speak, lambda index : updateSequence(currentNode, sequence, index))

    speak.generateSequence()

def mazeDemo() -> None:

    def printMazeNode(x, y, value):
        print(x, y, mazes.NodeValue(value))
        
    print(mazes.MazeAlgorithm.ALDOUS_BRODER)
    mazes.generateMaze(10, 10, True, mazes.MazeAlgorithm.ALDOUS_BRODER, printMazeNode)
    print("Growing Tree Custom Selection")
    mazes.generateGrowingTreeWithCustomSelection(10, 10, True, lambda nextNodesLength : nextNodesLength - 2 if nextNodesLength - 2 > 0 else 0, printMazeNode)
    print("Blobby Division")
    mazes.generateBlobbyDivisionWithCustomThreshold(10, 10, True, 7, printMazeNode)

def levelGenerationDemo() -> None:

    def addNode(position : math.Vector3):
        print(position)

    data = level_generation.GenerationData(10, 1, math.Vector3(0, 0, 0))

    print("Simple level generation")
    level_generation.simpleGeneration(data, math.Axes.POSITIVE_X, addNode)
    print("Multi Dimension Generation")
    level_generation.multiDimensionGeneration(data, math.Axes.XYZ, True, addNode)


def main() -> None:
    combinationsDemo()
    mazeDemo()
    levelGenerationDemo()

main()
