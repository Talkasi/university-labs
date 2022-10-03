# Find out in what part of the butterfly the point is
x = float(input("Enter x: "))
y = float(input("Enter y: "))
status = 0

# Left upper wing
if -9 <= x <= -1:
    y_up = -1 / 8 * (x + 9) ** 2 + 8
    y_down = 1 / 49 * (x + 1) ** 2 if -8 <= x <= -1 else 7 * (x + 8) ** 2 + 1
    if y_down <= y <= y_up:
        status = 1
        print("This point is in the area of the left upper wing.")

# Right upper wing
if 1 <= x <= 9:
    y_up = -1 / 8 * (x + 9) ** 2 + 8
    y_down = 1 / 49 * (x - 1) ** 2 if 1 <= x <= 8 else 7 * (x - 8) ** 2 + 1
    if y_down <= y <= y_up:
        status = 1
        print("This point is in the area of the right upper wing.")

# Body
if -1 <= x <= 1:
    y_up = -4 * x ** 2 + 2
    y_down = 4 * x ** 2 - 6
    if y_down <= y <= y_up:
        status = 1
        print("This point is in the area of the body.")

# Left lower wing
if -8 <= x <= 0:
    y_up = -x ** 2 / 16
    if -8 <= x <= -2:
        y_down = 1 / 3 * (x + 5) ** 2 - 7
    elif -2 <= x <= -1:
        y_down = -2 * (x + 1) ** 2 - 2
    else:
        y_down = -4 * x ** 2 + 2
    if y_down <= y <= y_up:
        status = 1
        print("This point is in the area of the left lower wing.")

# Right upper wing
if 0 <= x <= 8:
    y_up = -x ** 2 / 16
    if 2 <= x <= 8:
        y_down = 1 / 3 * (x - 5) ** 2 - 7
    elif 1 <= x <= 2:
        y_down = -2 * (x - 1) ** 2 - 2
    else:
        y_down = -4 * x ** 2 + 2
    if y_down <= y <= y_up:
        status = 1
        print("This point is in the area of the right lower wing.")

# Right mustache
if 0 <= x <= 2 and (y == 3 / 2 * x + 2):
    status = 1
    print("This point is on the right mustache.")

# Left mustache
if -2 <= x <= 0 and (y == - 3 / 2 * x + 2):
    status = 1
    print("This point is on the left mustache.")

# Nothing
if status == 0:
    print("This point is out of the area of the butterfly.")
