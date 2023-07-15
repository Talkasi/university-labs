import time
import pygame
class SpriteSheet:
    def __init__(self, image):
        self.sheet = image

    def get_image(self, frame, width, height, scale, colour):
        image = pygame.Surface((width, height)).convert_alpha()
        image.blit(self.sheet, (0, 0), ((frame * width), 0, width, height))
        image = pygame.transform.scale(image, (width * scale, height * scale))
        image.set_colorkey(colour)

        return image


pygame.init()

SCREEN_WIDTH = 500
SCREEN_HEIGHT = 500

screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Spritesheets')

sprite_sheet_image = pygame.image.load('images/doux.png').convert_alpha()
sprite_sheet = SpriteSheet(sprite_sheet_image)

sprite_sheet_image_mirror = pygame.image.load('images/doux_mirror.png').convert_alpha()
sprite_sheet_mirror = SpriteSheet(sprite_sheet_image_mirror)

BG = (50, 50, 50)
BLACK = (0, 0, 0)
IMAGE_WIDTH = 24
IMAGE_SCALED_WIDTH = IMAGE_WIDTH * 3

frames = [sprite_sheet.get_image(0, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
          sprite_sheet.get_image(1, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
          sprite_sheet.get_image(2, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
          sprite_sheet.get_image(3, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
          sprite_sheet.get_image(4, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
          sprite_sheet.get_image(5, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
          sprite_sheet.get_image(6, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
          sprite_sheet.get_image(7, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
          sprite_sheet.get_image(8, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
          sprite_sheet.get_image(9, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK)
          ]
frames_mirror = [sprite_sheet_mirror.get_image(23, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
                 sprite_sheet_mirror.get_image(22, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
                 sprite_sheet_mirror.get_image(21, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
                 sprite_sheet_mirror.get_image(20, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
                 sprite_sheet_mirror.get_image(19, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
                 sprite_sheet_mirror.get_image(18, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
                 sprite_sheet_mirror.get_image(17, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
                 sprite_sheet_mirror.get_image(16, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
                 sprite_sheet_mirror.get_image(15, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK),
                 sprite_sheet_mirror.get_image(14, IMAGE_WIDTH, IMAGE_WIDTH, 3, BLACK)]
run = True
x = 0
y = 0
cur_frame_n = 0
cur_frame_state = 0
step = 10
while run:
    # update background
    screen.fill(BG)
    # event handler
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
    keys = pygame.key.get_pressed()

    x += (keys[pygame.K_RIGHT] - keys[pygame.K_LEFT]) * step
    if keys[pygame.K_RIGHT] - keys[pygame.K_LEFT] > 0:
        cur_frame_state = 0
    if keys[pygame.K_RIGHT] - keys[pygame.K_LEFT] < 0:
        cur_frame_state = 1

    y += (keys[pygame.K_DOWN] - keys[pygame.K_UP]) * step

    if x < 0:
        x = 0
    if x > SCREEN_WIDTH - IMAGE_SCALED_WIDTH:
        x = SCREEN_WIDTH - IMAGE_SCALED_WIDTH

    if y < 0:
        y = 0
    if y > SCREEN_HEIGHT - IMAGE_SCALED_WIDTH:
        y = SCREEN_HEIGHT - IMAGE_SCALED_WIDTH

    # show frame image
    if cur_frame_state == 0:
        screen.blit(frames[cur_frame_n], (x, y))
    if cur_frame_state == 1:
        screen.blit(frames_mirror[cur_frame_n], (x, y))
    cur_frame_n = (cur_frame_n + 1) % 7

    pygame.display.update()
    time.sleep(0.1)

pygame.quit()
