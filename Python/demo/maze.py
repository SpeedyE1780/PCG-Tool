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

def clamp(value, minValue, maxValue):
    return max(minValue, min(value, maxValue))

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
    STARTX = 50
    STARTY = 50

    def __init__(self, x, y, adjacent):
        self.x = x * (Node.LENGTH + Node.OFFSET) + Node.STARTX
        self.y = y * (Node.LENGTH + Node.OFFSET) + Node.STARTY
        self.adjacentNodes = adjacent

    def draw(self):
        drawNode(self.x, self.y, Node.LENGTH, self.adjacentNodes)


nodes = {}
radius = 5
px = 0
py = 0


def drawPlayer(x, y):
    x = x * (Node.LENGTH + Node.OFFSET) + (Node.STARTX + Node.LENGTH * 0.5)
    y = y * (Node.LENGTH + Node.OFFSET) + (Node.STARTY + Node.LENGTH * 0.5)

    pygame.draw.circle(screen, white, (x, y), radius)
    print(x, y)


mazes.generateMaze(
    10,
    10,
    True,
    mazes.MazeAlgorithm.ALDOUS_BRODER,
    lambda x, y, adjacent: nodes.update({(x, y): Node(x, y, adjacent)}),
)

while Running:
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                Running = False
            if event.key == pygame.K_UP:
                py -= 1
            if event.key == pygame.K_DOWN:
                py += 1
            if event.key == pygame.K_LEFT:
                px -= 1
            if event.key == pygame.K_RIGHT:
                px += 1

    px = clamp(px, 0, 9)
    py = clamp(py, 0, 9)
    screen.fill(black)

    for node in nodes:
        nodes[node].draw()

    drawPlayer(px, py)

    pygame.display.update()

pygame.quit()
