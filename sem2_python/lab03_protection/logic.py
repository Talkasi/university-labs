from PIL import Image

img = Image.open('cat.png').convert("RGB")
img_size = img.size

step_x = int(img_size[1] / 7)
step_y = int(img_size[0] / 7)
for y in range(0, img_size[1]):
    for x in range(0, img_size[0]):
        pix = img.getpixel((x, y))

        if step_x - 20 < x < step_x or step_y - 20 < y < step_y:
            pix = (255, 0, 0)
            if x == step_x - 1:
                step_x += int(img_size[1] / 7)
            if y == step_y - 1:
                step_y += int(img_size[0] / 7)

        img.putpixel((x, y), pix)

step_x = int(img_size[1] / 7)
step_y = int(img_size[0] / 7)
for x in range(0, img_size[0]):
    for y in range(0, img_size[1]):
        pix = img.getpixel((x, y))

        if step_x - 20 < x < step_x or step_y - 20 < y < step_y:
            pix = (255, 0, 0)
            if x == step_x - 1:
                step_x += int(img_size[1] / 7)
            if y == step_y - 1:
                step_y += int(img_size[0] / 7)

        img.putpixel((x, y), pix)

img.save('new_cat.png', "PNG")
