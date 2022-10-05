import math

x_min = 0
x_max = 1
x_step = 0.05

# Print a table of values for the functions - x equals to y
print("┌─────────┬────────────┬────────────┬────────────┐")
print("│    x    │     y1     │     y2     │     y3     │")
print("├─────────┼────────────┼────────────┼────────────┤")

x = x_min
y_min = math.inf
y_max = -math.inf

while x <= x_max + x_step:
    y1 = x ** 3 - 6.5 * x ** 2 - 31.3 * x + 2.32
    # Find max and min for scaling y part
    y_min, y_max = min(y_min, y1), max(y_max, y1)

    y2 = x ** 2 - math.sin(math.pi * x)
    y3 = y1 ** 2 - y2 ** 2

    print("│_  {:4.2g}  │_ {:6.2g}    │_ {:8.2g}  │_ {:8.2g}  │".format(x, y1, y2, y3))

    x += x_step
print("└─────────┴────────────┴────────────┴────────────┘")

# Ask user for the number of '
while True:
    n = int(input("Enter number (4 <= n <= 8) of ': "))
    if 4 <= n <= 8: break
    print("\nNumber should be an integer from 4 to 8. Please try again.")

# Start graphic's table
print("┌─────────┬────────────────────────────────────────────────────────────────────────────────────────┐")

i = 0
x = x_min
y = y_min
s_out = ""
scale = 84

# Scaling y part
k = math.ceil((scale - n * 9) / (n - 1))
while i < n:
    if i == n - 1:
        s_out += '{: <9.4}'.format(y)
    elif i == n - 2:
        s_out += '{: <9.4}'.format(y) + k * " " + (scale - len(s_out) - k - 15) * " "
    else:
        s_out += '{: <9.4}'.format(y) + k * " "

    x += x_step
    y += (y_max - y_min) / (n - 1)
    i += 1

# Format s_out
s_out = "│         │ " + s_out + "│"
print(s_out)

# Close scaling y part line
print("├─────────┼────────────────────────────────────────────────────────────────────────────────────────┤")

# Graphic stuff
scale = 77
x = x_min
while x <= x_max + x_step:
    y1 = x ** 3 - 6.5 * x ** 2 - 31.3 * x + 2.32
    k = math.ceil(abs(y_min) * scale / (y_max - y_min))
    k1 = y1 * scale // (y_max - y_min)
    k2 = scale - k1
    if k1 > 0:
        print("│_  {:4.2g}  │    ".format(x) + " " * int(k) + "|" + " " * int(k1) +
              "*" + " " * int(scale - k - k1 + 5) + "│")
    else:
        print("│_  {:4.2g}  │    ".format(x) + " " * int(k + k1) + "*" + " " * int(-k1 - 1) +
              "|" + " " * 10 + "│")
    x += x_step

# Close graphic's table
print("└─────────┴────────────────────────────────────────────────────────────────────────────────────────┘")


# Found main and max for the additional task
# Derivative of the first function is  * x ** 2 - 13 * x - 31.3
# Solving quadratic equation (3 * x ** 2 - 13 * x - 31.3 = 0) by lab2
x_1 = 6.056111
x_2 = -1.722778

y1_1 = x_1 ** 3 - 6.5 * x_1 ** 2 - 31.3 * x_1 + 2.32
y1_2 = x_2 ** 3 - 6.5 * x_2 ** 2 - 31.3 * x_2 + 2.32
print("Minimum of the first function is {:.5g}".format(min(y1_1, y1_2)))


# Derivative of the second function equals to 0, -> 2 * x - math.pi * math.cos(math.pi * x) = 0
x = math.cos(math.pi * x) * math.pi / 2
y2_1 = x ** 2 - math.sin(math.pi * x)
print("Maximum of the second function is {:.5g}".format(y2_1))
