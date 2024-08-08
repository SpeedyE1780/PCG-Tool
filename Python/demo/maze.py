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


def drawNode(x, y, length, up, down, left, right):
    if up:
        pygame.draw.line(screen, white, (x, y), (x + length, y))
    if down:
        pygame.draw.line(screen, white, (x, y + length), (x + length, y + length))

    if left:
        pygame.draw.line(screen, white, (x, y), (x, y + length))
    if right:
        pygame.draw.line(screen, white, (x + length, y), (x + length, y + length))


while Running:
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                Running = False

    screen.fill(black)
    drawNode(20, 20, 20, True, True, True, True)
    pygame.display.update()

pygame.quit()
