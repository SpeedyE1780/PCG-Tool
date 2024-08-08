import pygame
import pygame.locals
from pcg import mazes

pygame.init()

resolution = (1280, 720)
black = (0, 0, 0)
white = (255, 255, 255)

screen = pygame.display.set_mode(resolution)
screen.fill(black)

Running = True


def drawNode(x, y, length, adjacentNodes):
    if (adjacentNodes & mazes.NodeValue.BACKWARD.value) == 0:
        pygame.draw.line(screen, white, (x, y), (x + length, y))
    if (adjacentNodes & mazes.NodeValue.FORWARD.value) == 0:
        pygame.draw.line(screen, white, (x, y + length), (x + length, y + length))

    if (adjacentNodes & mazes.NodeValue.LEFT.value) == 0:
        pygame.draw.line(screen, white, (x, y), (x, y + length))
    if (adjacentNodes & mazes.NodeValue.RIGHT.value) == 0:
        pygame.draw.line(screen, white, (x + length, y), (x + length, y + length))


class Node:
    LENGTH = 20
    OFFSET = 0

    def __init__(self, x, y, adjacent):
        self.x = x * (Node.LENGTH + Node.OFFSET)
        self.y = y * (Node.LENGTH + Node.OFFSET)
        self.adjacentNodes = adjacent

    def draw(self):
        drawNode(self.x, self.y, Node.LENGTH, self.adjacentNodes)


nodes = []

mazes.generateMaze(
    10,
    10,
    True,
    mazes.MazeAlgorithm.ALDOUS_BRODER,
    lambda x, y, adjacent: nodes.append(Node(x, y, adjacent)),
)

while Running:
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                Running = False

    screen.fill(black)
    for node in nodes:
        node.draw()

    pygame.display.update()

pygame.quit()
