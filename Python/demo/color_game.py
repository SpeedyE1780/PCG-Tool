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

Running = True
clock = pygame.time.Clock()
fps = 60
nextTime = 0.5
time = nextTime
currentNodeIndex = 0

sequence = []
nodes = [red, green, blue, yellow]

node = combinations.SequenceNode()
node.addNextNodes(nodes)


def updateSequence(index):
    if index == -1:
        return 0

    sequence.append(nodes[index])
    return len(nodes[index])


combinations.generateCyclicSequence(node, 3, updateSequence)

while Running:
    deltaTime = clock.tick(fps)
    time -= deltaTime * 0.001

    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                Running = False

    screen.fill(black)

    pygame.draw.circle(
        screen, red, [600, 320], 20, 0 if sequence[currentNodeIndex] == red else 1
    )
    pygame.draw.circle(
        screen, green, [560, 360], 20, 0 if sequence[currentNodeIndex] == green else 1
    )
    pygame.draw.circle(
        screen, blue, [640, 360], 20, 0 if sequence[currentNodeIndex] == blue else 1
    )
    pygame.draw.circle(
        screen, yellow, [600, 400], 20, 0 if sequence[currentNodeIndex] == yellow else 1
    )

    pygame.display.update()

    if time <= 0:
        time = nextTime
        currentNodeIndex += 1

        if currentNodeIndex >= len(sequence):
            Running = False

pygame.quit()
