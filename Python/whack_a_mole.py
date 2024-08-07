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

def drawGrid(startX: int, startY :int, gridWidth: int, gridHeight : int, nodeSize : int, offset : int):
    
    currentX = startX
    currentY = startY

    for w in range(gridWidth):
        for h in range(gridHeight):
            pygame.draw.circle(screen, white, [currentX, currentY], nodeSize, 3)
            currentY += nodeSize * 2 + offset
        currentY = startY
        currentX += nodeSize * 2 + offset
    

while Running:
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                Running = False
    screen.fill(black)
    drawGrid(100, 100, 8, 8, 10, 5)
    pygame.display.update()

pygame.quit()
