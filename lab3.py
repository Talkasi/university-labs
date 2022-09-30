eps = 1e-9

while True:
    x1 = float(input("Enter x of the first point: "))
    y1 = float(input("Enter y of the first point: "))

    x2 = float(input("\nEnter x of the second point: "))
    y2 = float(input("Enter y of the second point: "))

    x3 = float(input("\nEnter x of the third point: "))
    y3 = float(input("Enter y of the third point: "))

    # Compute sides of the triangle
    side1 = ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5
    side2 = ((x1 - x3) ** 2 + (y1 - y3) ** 2) ** 0.5
    side3 = ((x3 - x2) ** 2 + (y3 - y2) ** 2) ** 0.5

    # Sort sides of the triangle
    max_side = max(side1, side2, side3)
    min_side = min(side1, side2, side3)
    middle_side = side1 + side2 + side3 - max_side - min_side

    # Check the entered parameters
    if max_side >= min_side + middle_side:
        print("\nThere is no triangle created with such points. Please check the parameters and try again.\n")
    else:
        break

print("\nThe length of the first side of the triangle is {:.5g}.".format(min_side))
print("The length of the second side of the triangle is {:.5g}.".format(middle_side))
print("The length of the third side of the triangle is {:.5g}.".format(max_side))

# Compute median size
cos_a = (max_side ** 2 + middle_side ** 2 - min_side ** 2) / 2 / max_side / middle_side
median = ((max_side / 2) ** 2 + middle_side ** 2 - middle_side * max_side * cos_a) ** 0.5
print("\nThe length of the median is {:.5g}.".format(median))

# Check if triangle is isosceles
if max_side - middle_side <= eps or middle_side - min_side <= eps:
    print("\nThis triangle is isosceles.")
else:
    print("\nThis triangle isn't isosceles.")

x = float(input("\nEnter x of the point to check: "))
y = float(input("Enter y of the point to check: "))

# Compute a distance from the point to the triangle vertices
side1_additional = ((x1 - x) ** 2 + (y1 - y) ** 2) ** 0.5
side2_additional = ((x2 - x) ** 2 + (y2 - y) ** 2) ** 0.5
side3_additional = ((x3 - x) ** 2 + (y3 - y) ** 2) ** 0.5

# Compute the perimeter, area and height of each created triangle
p_t1 = (side2_additional + side1_additional + side1) / 2
s_t1 = (p_t1 * (p_t1 - side1) * (p_t1 - side1_additional) * (p_t1 - side2_additional)) ** 0.5
d1 = 2 * s_t1 / side1

p_t2 = (side1_additional + side3_additional + side2) / 2
s_t2 = (p_t2 * (p_t2 - side2) * (p_t2 - side3_additional) * (p_t2 - side1_additional)) ** 0.5
d2 = 2 * s_t2 / side2

p_t3 = (side2_additional + side3_additional + side3) / 2
s_t3 = (p_t3 * (p_t3 - side3) * (p_t3 - side3_additional) * (p_t3 - side2_additional)) ** 0.5
d3 = 2 * s_t3 / side3

# Compute the perimeter, area and height of the given triangle
p = (side1 + side2 + side3) / 2
s = (p * (p - side1) * (p - side2) * (p - side3)) ** 0.5

# Check if the point is in the area of the triangle
if abs(s_t3 + s_t2 + s_t1 - s) <= eps:
    print("\nThis point is in the area of the triangle. The smallest distance is {:.5g}.".format(min(d1, d2, d3)))
else:
    print("\nThis point is out of the area of the triangle.")
