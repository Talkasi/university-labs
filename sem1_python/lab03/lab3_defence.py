x1 = int(input("Enter x of the first point: "))
y1 = int(input("Enter y of the first point: "))

x2 = int(input("\nEnter x of the second point: "))
y2 = int(input("Enter y of the second point: "))

x3 = int(input("\nEnter x of the third point: "))
y3 = int(input("Enter y of the third point: "))

# Computing sides of the triangle
side1 = ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5
side2 = ((x3 - x2) ** 2 + (y3 - y2) ** 2) ** 0.5
side3 = ((x1 - x3) ** 2 + (y1 - y3) ** 2) ** 0.5
print("\nSides before sorting - {:.7g}, {:.7g}, {:.7g}".format(side1, side2, side3))

# Sort sides of the triangle: side1 <= side2 <= side3
if side1 > side2:
    side1, side2 = side2, side1
if side3 < side1:
    side1, side2, side3 = side3, side1, side2
if side3 < side2:
    side2, side3 = side3, side2
print("Sides after sorting - {:.7g}, {:.7g}, {:.7g}".format(side1, side2, side3))

# Computing perimeter, area and height of the given triangle
p = (side1 + side2 + side3) / 2
s = (p * (p - side1) * (p - side2) * (p - side3)) ** 0.5
h = 2 * s / side3

print("\nThe length of the heigth drown from the biggest angle is {:.5g}.".format(h))
