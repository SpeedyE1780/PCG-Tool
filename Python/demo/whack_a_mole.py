import pygame
import pygame.locals
from pcg import combinations

pygame.init()

resolution = (1280, 720)
black = (0, 0, 0)
white = (255, 255, 255)

screen = pygame.display.set_mode(resolution)
screen.fill(black)

Running = True
score = 0


class Mole:
    def __init__(self, x, y, radius):
        self.x = x
        self.y = y
        self.radius = radius
        self.hasMole = False

    def whack(self, x, y):
        if x in range(self.x - self.radius, self.x + self.radius) and y in range(
            self.y - self.radius, self.y + self.radius
        ):
            global score
            score += 1
            self.hasMole = False

        return self.hasMole

    def draw(self):
        pygame.draw.circle(screen, white, [self.x, self.y], self.radius)

        if self.hasMole:
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

clock = pygame.time.Clock()
fps = 60
gameTime = 30
resetTime = 2500
time = resetTime

while Running:
    deltaTime = clock.tick(fps)
    time -= deltaTime
    gameTime -= deltaTime * 0.001

    if gameTime < 0:
        gameOverText = pygame.font.Font(None, 36).render("GAME OVER!", True, white)
        screen.blit(gameOverText, [1280 * 0.5, 720 * 0.5])
        pygame.display.update()

        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    Running = False

        continue

    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                Running = False

        if event.type == pygame.MOUSEBUTTONUP:
            x, y = pygame.mouse.get_pos()
            moleRemaining = False

            for mole in moles:
                moleRemaining |= mole.whack(x, y)

    screen.fill(black)

    if not moleRemaining or time <= 0:
        moles = drawGrid(100, 100, 3, 3, 10, 5)
        combinations.generateCombinationWithMinimumElements(
            moles,
            1,
            lambda index, included: moles[index].addMole() if included else None,
        )
        moleRemaining = True
        time = resetTime

    for mole in moles:
        mole.draw()

    scoreText = pygame.font.Font(None, 36).render(
        "Score: {0}".format(score), True, white
    )
    screen.blit(scoreText, [1000, 100])

    gameTimeText = pygame.font.Font(None, 36).render(
        "Time: {0:.2f}".format(gameTime), True, white
    )
    screen.blit(gameTimeText, [1000, 40])
    pygame.display.update()


pygame.quit()
