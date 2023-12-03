import time
import pygame

pygame.init()

SCREEN_WIDTH = 500
SCREEN_HEIGHT = 500
STEP = 25
R_VEL = 5
R_END = 35 + 5 * 7
Y_HIGHEST = 270
Y_LOWEST = SCREEN_WIDTH - 35

screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Spritesheets')

BG = (50, 50, 50)

run = True
y_cur = Y_HIGHEST
direction = 1
r = 35
y_balloon = 200
colors = ["red", "yellow", "green", "blue"]
i = 0
while run:
    # update background
    screen.fill(BG)
    # event handler
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False

    if R_END > r:
        y_cur += STEP * direction
        if y_cur > Y_LOWEST:
            y_cur = Y_LOWEST
            direction = -1

        if y_cur < Y_HIGHEST:
            y_cur = Y_HIGHEST
            r += R_VEL
            y_balloon -= R_VEL
            direction = 1
    else:
        y_balloon -= R_VEL * 2
        if y_balloon < -R_END * 2:
            y_cur = Y_HIGHEST
            direction = 1
            r = 35
            y_balloon = 200

    pygame.draw.rect(screen, (255, 255, 255), (200, y_cur, 100, 35))
    pygame.draw.rect(screen, (255, 255, 255), (235, y_cur, 30, 500 - y_cur))

    pygame.draw.line(screen, (255, 255, 255), (200, 270), (200, 500))
    pygame.draw.line(screen, (255, 255, 255), (300, 270), (300, 500))

    pygame.draw.line(screen, (255, 255, 255), (200, 270), (225, 220))
    pygame.draw.line(screen, (255, 255, 255), (300, 270), (275, 220))

    pygame.draw.circle(screen, colors[i % 4], (250, y_balloon), r, draw_top_left=True)
    pygame.draw.circle(screen, colors[(i + 1) % 4], (250, y_balloon), r, draw_top_right=True)
    pygame.draw.circle(screen, colors[(i + 2) % 4], (250, y_balloon), r, draw_bottom_left=True)
    pygame.draw.circle(screen, colors[(i + 3) % 4], (250, y_balloon), r, draw_bottom_right=True)

    i = (i + 1) % 4
    pygame.display.update()
    time.sleep(0.1)
