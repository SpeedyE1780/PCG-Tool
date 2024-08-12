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
clock = pygame.time.Clock()
fps = 60

while Running:
    deltaTime = clock.tick(fps)

    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                Running = False

    screen.fill(black)

    pygame.display.update()


pygame.quit()
