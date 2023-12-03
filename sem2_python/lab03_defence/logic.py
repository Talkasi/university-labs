from PIL import Image
from PIL import ImageDraw

color = "green"

img = Image.open('cat.png').convert("RGB")
img_size = img.size

draw = ImageDraw.Draw(img)
for i in range(0, img_size[1], img_size[1] //  7):
    draw.line((0, i) + (img_size[0], i), width=5, fill=color)

for i in range(0, img_size[0], img_size[0] //  7):
    draw.line((i, 0) + (i, img_size[1]), width=5, fill=color)

img.save('new_cat.png', "PNG")
