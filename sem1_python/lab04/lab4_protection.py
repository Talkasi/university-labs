import math

x_min = float(input("Enter x min: "))
x_max = float(input("Enter x max: "))
x_step = float(input("Enter x step: "))

y_min = math.inf
y_max = - math.inf
n = math.ceil((x_max + x_step - x_min) / x_step)
if n == 0:
    print("Error. There is no place to make a step.")
else:
    x = x_min
    for i in range(n):
        if x > x_max: break
        y = math.sin(x)
        print(x, y)
        y_min = min(y_min, y)
        y_max = max(y_max, y)
        x += x_step

    # Graphics y scaling part
    print("-" * 63)
    print("|         |{:8.8f}                            {:8.8f} |".format(y_min, y_max))
    print("-" * 63)

    # Graphics part
    scale = 38
    x = x_min
    for i in range(n):
        if x > x_max: break
        y = math.sin(x)
        s_out = "| {:7.2f} |    ".format(x)

        k = math.ceil(abs(y_min) * scale / (y_max - y_min))  # Place of zero
        k1 = math.ceil(y * scale / (y_max - y_min))  # Place of y using zero
        k2 = scale - k1  # What is rest to save the table

        if y_max >= 0:  # if (y_max >= 0) we need zero line, else we don't
            if k1 > 0:  # Check if current y < 0, then * position is lower than | position
                print("| {:7.2f} |    ".format(x) + " " * int(k) + "|" + " " * int(k1) +
                      "*" + " " * int(scale - k - k1 + 7) + "|")
            else:
                p = "" if (int(-k1) == 0) else "*"  # Save the table if * == |
                print("| {:7.2f} |    ".format(x) + " " * int(k + k1) + p + " " * int(-k1 - 1) +
                      "|" + " " * (scale - k + 8) + "|")
        else:
            p = "" if (int(scale - k - k1 + 9) == 0) else "*"  # Save the table if * == |
            print("| {:7.2f} |    ".format(x) + " " * int(k + k1) + p + " " * int(scale - k - k1 + 8) + "|")
        x += x_step

print("-" * 63)
