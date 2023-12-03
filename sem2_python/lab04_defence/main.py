import tkinter as tk
from math import inf

lines = []
CANVAS_WIDTH = 500
CANVAS_HEIGHT = 500

n = int(input("Enter number of lines: "))
for i in range(n):
    points = list(map(float, input("Enter x, y of the first point of the line: ").strip().split()))
    points += list(map(float, input("Enter x, y of the second point of the line: ").strip().split()))
    lines.append(points)

root = tk.Tk()
root.resizable(width=False, height=False)
root.title('Lab04_protection')

canvas = tk.Canvas(bg='white', width=CANVAS_WIDTH, height=CANVAS_HEIGHT)

min_k = inf
min_b = inf
min_i = 0
f = True
for i in range(n):
    x1 = lines[i][0]
    y1 = lines[i][1]
    x2 = lines[i][2]
    y2 = lines[i][3]

    try:
        k = (y1 - y2) / (x1 - x2)
        if k == 0:
            raise Exception
    except:
        if x1 == x2:
            canvas.create_line(x1, 0, x2, CANVAS_HEIGHT, width=2)
        else:
            f = False
            canvas.create_line(0, y1, CANVAS_WIDTH, y2, fill='green', width=4)
        continue

    b = y2 - k * x2
    if k < min_k:
        min_k = k
        min_b = b
        min_i = i

    # y = kx + b
    # x = (y - b) / k
    canvas.create_line(-b / k, b, (CANVAS_WIDTH - b) / k, k * CANVAS_WIDTH + b, width=2)

if f:
    canvas.create_line(-min_b / min_k, min_b, (CANVAS_WIDTH - min_b) / min_k, min_k * CANVAS_WIDTH + min_b,
                       fill='green', width=4)
canvas.grid()
root.mainloop()
