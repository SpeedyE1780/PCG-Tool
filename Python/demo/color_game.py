import pygame
import pygame.locals
from pcg import combinations

pygame.init()

resolution = (1280, 720)
black = (0, 0, 0)
white = (255, 255, 255)

red = (255, 0, 0)
green = (0, 255, 0)
blue = (0, 0, 255)
yellow = (255, 255, 0)

screen = pygame.display.set_mode(resolution)
screen.fill(black)


class ColorButton:
    Radius = 20

    def __init__(self, color, coordinates):
        self.color = color
        self.coordinates = coordinates
        self.isHighlighted = False

    def draw(self, highlight):
        pygame.draw.circle(
            screen,
            self.color,
            self.coordinates,
            ColorButton.Radius,
            0 if self.isHighlighted and highlight else 1,
        )

    def isPressed(self, x, y):
        return x in range(
            self.coordinates[0] - ColorButton.Radius,
            self.coordinates[0] + ColorButton.Radius,
        ) and y in range(
            self.coordinates[1] - ColorButton.Radius,
            self.coordinates[1] + ColorButton.Radius,
        )

    def toggleHighlight(self, highlight):
        self.isHighlighted = highlight


Running = True
clock = pygame.time.Clock()
fps = 60
nextTime = 0.5
time = nextTime
currentNodeIndex = 0
highlight = False
waitForUser = False

sequence = []
nodes = [
    ColorButton(red, [600, 320]),
    ColorButton(green, [560, 360]),
    ColorButton(blue, [640, 360]),
    ColorButton(yellow, [600, 400]),
]

node = combinations.SequenceNode()
node.addNextNodes(nodes)


def updateSequence(index):
    if index == -1:
        return 0

    sequence.append(nodes[index])
    return node.nextNodeCount


combinations.generateCyclicSequence(node, 100, updateSequence)
sequence[0].toggleHighlight(True)
lastPressed = None
currentSequenceLength = 1

while Running:
    deltaTime = clock.tick(fps)
    time -= deltaTime * 0.001

    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                Running = False
        if event.type == pygame.MOUSEBUTTONUP and waitForUser:
            x, y = pygame.mouse.get_pos()
            for node in nodes:
                if node.isPressed(x, y):

                    if not lastPressed == None:
                        lastPressed.toggleHighlight(False)
                    
                    node.toggleHighlight(True)
                    time = nextTime
                    highlight = True
                    lastPressed = node

    screen.fill(black)

    if not waitForUser:
        for node in nodes:
            node.draw(highlight)

    else:
        for node in nodes:
            node.draw(highlight)

    pygame.display.update()

    if time <= 0 and not waitForUser:
        time = nextTime

        if highlight:
            sequence[currentNodeIndex].toggleHighlight(False)
            currentNodeIndex += 1
            if currentNodeIndex < currentSequenceLength:
                sequence[currentNodeIndex].toggleHighlight(True)

        highlight = not highlight

        if currentNodeIndex >= currentSequenceLength:
            currentNodeIndex = 0
            waitForUser = True
            
    if time <= 0 and waitForUser and highlight:
        highlight = False
        lastPressed.toggleHighlight(False)

pygame.quit()
