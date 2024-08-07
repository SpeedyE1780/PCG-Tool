import pygame
import pygame.locals
from pcg import combinations, math

pygame.init()

resolution = (1280, 720)
black = (0, 0, 0)
white = (255, 255, 255)

screen = pygame.display.set_mode(resolution)
screen.fill(black)

Running = True


class Mole:
    def __init__(self, x, y, radius):
        self.x = x
        self.y = y
        self.radius = radius
        self.hasMole = False

    def draw(self):
        pygame.draw.circle(screen, white, [self.x, self.y], self.radius)
        if(self.hasMole):
            pygame.draw.circle(screen, black, [self.x, self.y], self.radius * 0.5)
        
    def addMole(self):
        self.hasMole = True


def drawGrid(
    startX: int,
    startY: int,
    gridWidth: int,
    gridHeight: int,
    nodeSize: int,
    offset: int,
) -> list[Mole]:
    currentX = startX
    currentY = startY

    moles = []

    for _ in range(gridWidth):
        for _ in range(gridHeight):
            moles.append(Mole(currentX, currentY, nodeSize))
            currentY += nodeSize * 2 + offset

        currentY = startY
        currentX += nodeSize * 2 + offset

    return moles

moleRemaining = False
moles = []

while Running:
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                Running = False

    screen.fill(black)
    
    if not moleRemaining:
        moles = drawGrid(100, 100, 3, 3, 10, 5)
        combinations.generateCombinationWithMinimumElements(moles, 1, lambda index, included: moles[index].addMole() if included else None)
        moleRemaining = True

    for mole in moles:
        mole.draw()

    pygame.display.update()

pygame.quit()
