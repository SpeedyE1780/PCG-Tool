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

while Running:
    deltaTime = clock.tick(fps)

    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                Running = False

    screen.fill(black)

    pygame.draw.circle(screen, red, [600, 320], 20,  1)
    pygame.draw.circle(screen, green, [560, 360], 20,  1)
    pygame.draw.circle(screen, blue, [640, 360], 20,  1)
    pygame.draw.circle(screen, yellow, [600, 400], 20,  1)

    pygame.display.update()


pygame.quit()
