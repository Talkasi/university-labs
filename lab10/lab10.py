# Kuracheva K. D., ИУ7-13Б
'''
Программа вычисляет интеграл по 2м заданнным по варианту методам:
- левых прямоугольников
- 3/8
'''


def function(x):
    try:
        f = x ** 3
        if f is None:
            print("[!]Error. Function is undefined in x = {:.7g}.".format(x))
            print("Run the program again and enter correct x_start and x_end")
            exit()
        return f
    except:
        print("[!]Error. Function is undefined in x = {:.7g}.".format(x))
        print("Run the program again and enter correct x_start and x_end")
        exit()


def antiderivative_function(x):
    try:
        f = x ** 4 / 4
        if f is None:
            print("[!]Error. Function is undefined in x = {:.7g}.".format(x))
            print("Run the program again and enter correct x_start and x_end")
            exit()
        return f
    except:
        print("[!]Error. Antiderivative function is undefined in x = {:.7g}".format(x))
        print("Run the program again and enter correct x_start and x_end")
        exit()


def input_checking_errors(message_input, specifier):
    parameter, flag = 0, 0
    while flag == 0:
        try:
            # specifier = 1 -> int
            # specifier = 0 -> float
            if specifier:
                parameter = int(input(message_input))
            else:
                parameter = float(input(message_input))

            flag = 1
        except:
            print("[!]Error. Number " + ("(int)" if specifier else "(float)") + " should be entered. Try again.")

    return parameter


def left_r_method(n):
    s_method1 = 0
    step = (x_end - x_start) / n
    x_current = x_start

    while abs(x_end - x_current) > eps:
        s_method1 += function(x_current) * step
        x_current += step

    return s_method1


def m3_8(n):
    s_method2 = 0
    step = (x_end - x_start) / n * 3
    for i in range(n // 3):
        a = x_start + step * i
        b = x_start + step * (i + 1)
        s_method2 += (function(a) + 3 * function((2 * a + b) / 3) + 3 * function((a + 2 * b) / 3) + function(
            b)) * step / 8

    return s_method2


# Input block
float_type, int_type = 0, 1
x_start = input_checking_errors("Enter start of the segment: ", float_type)
x_end = input_checking_errors("Enter end of the segment: ", float_type)

while x_end <= x_start:
    print("[!]Error. x_end should be bigger then x_start. Try again.")
    x_end = input_checking_errors("Enter end of the segment: ", float_type)

print("[!]Warning. Method 3/8 works only when number of segments to divide on is divisible by 3.")

n1_segments = input_checking_errors("Enter first number of segments to divide on: ", int_type)
while n1_segments < 1:
    print("[!]Error. Nuber of segments should be bigger then 0. Try again.")
    n1_segments = input_checking_errors("Enter first number of segments to divide on: ", int_type)

n2_segments = input_checking_errors("Enter second number of segments to divide on: ", int_type)

while n2_segments < 1:
    print("[!]Error. Nuber of segments should be bigger then 0. Try again.")
    n2_segments = input_checking_errors("Enter second number of segments to divide on: ", int_type)

# Computing block
eps = 1e-12

# Left rectangles
sum_v1_n1 = left_r_method(n1_segments)
sum_v1_n2 = left_r_method(n2_segments)

# 3/8
sum_v2_n1, sum_v2_n2 = 0, 0
if n1_segments % 3 == 0:
    sum_v2_n1 = m3_8(n1_segments)
if n2_segments % 3 == 0:
    sum_v2_n2 = m3_8(n2_segments)

print("┌─────────────┬──────────────────────┬──────────────────────┐")
print("│             │          N1          │          N2          │")
print("├─────────────┼──────────────────────┼──────────────────────┤")
print("│  Method #1  │" + " {:20.7g} ".format(sum_v1_n1) + "│" + " {:20.7g} ".format(sum_v1_n2) + "│")
print("├─────────────┼──────────────────────┼──────────────────────┤")
print("│  Method #2  │" + (" {:20.7g} ".format(sum_v2_n1) if n1_segments % 3 == 0 else "—".center(22)) + "│" + (
    " {:20.7g} ".format(sum_v2_n2) if n2_segments % 3 == 0 else "—".center(22)) + "│")
print("└─────────────┴──────────────────────┴──────────────────────┘")

expected = antiderivative_function(x_end) - antiderivative_function(x_start)
print("Expected value is: {:.7g}".format(expected))

absolute_v1_n1 = abs(sum_v1_n1 - expected)
absolute_v1_n2 = abs(sum_v1_n2 - expected)
absolute_v2_n1 = abs(sum_v2_n1 - expected)
absolute_v2_n2 = abs(sum_v2_n2 - expected)

relative_v1_n1 = absolute_v1_n1 / expected * 100
relative_v1_n2 = absolute_v1_n2 / expected * 100
relative_v2_n1 = absolute_v2_n1 / expected * 100
relative_v2_n2 = absolute_v2_n2 / expected * 100

print("┌─────────────┬─────────────────────────────────┬─────────────────────────────────┐")
print("│             │                N1               │                N2               │")
print("├─────────────┼────────────────┬────────────────┼────────────────┬────────────────┤")
print("│             │    absolute    │    relative    │    absolute    │    relative    │")
print("├─────────────┼────────────────┼────────────────┼────────────────┼────────────────┤")
print("│  Method #1  │" + " {:14.7g} ".format(absolute_v1_n1) + "│" + " {:14.7g} ".format(relative_v1_n1) + "│" +
      " {:14.7g} ".format(absolute_v1_n2) + "│" + " {:14.7g} ".format(relative_v1_n2) + "│")
print("├─────────────┼────────────────┼────────────────┼────────────────┼────────────────┤")

print("│  Method #2  │", end="")
if n1_segments % 3 != 0:
    print("—".center(16) + "│" + "—".center(16) + "│", end="")
else:
    print(" {:14.7g} ".format(absolute_v2_n1) + "│" + " {:14.7g} ".format(relative_v2_n1) + "│", end="")

if n2_segments % 3 != 0:
    print("—".center(16) + "│" + "—".center(16) + "│")
else:
    print(" {:14.7g} ".format(absolute_v2_n2) + "│" + " {:14.7g} ".format(relative_v2_n2) + "│")
'''
print("│  Method #2  │" + " {:14.7g} ".format(absolute_v2_n1) + "│" + " {:14.7g} ".format(relative_v2_n1) + "│"
          + " {:14.7g} ".format(absolute_v2_n2) + "│" + " {:14.7g} ".format(relative_v2_n2) + "│")
'''

print("└─────────────┴────────────────┴────────────────┴────────────────┴────────────────┘")

if abs(absolute_v1_n1) < abs(absolute_v2_n1):
    most_precise_method = 1
    least_precise_method = m3_8
else:
    most_precise_method = 2
    least_precise_method = left_r_method

print("The most precise is method #{:g}".format(most_precise_method))

eps_entered = input_checking_errors("Enter eps to compute: ", float_type)

n = 1 if most_precise_method == 2 else 3

m = least_precise_method(n)
m2 = least_precise_method(n * 2)
print(abs(m - m2))
while abs(m - m2) >= eps_entered:
    n *= 2
    m, m2 = m2, least_precise_method(n * 2)

print("Number of segments needed is {:.7g}".format(n))
