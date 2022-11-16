# Kuracheva K. D., ИУ7-13Б
'''
Курачева Ксения
левых
прямоугольников
3/8

'''


def function(x):
    return x


def antiderivative_function(x):
    return 1 / 2 * x ** 2


def input_checking_errors(message_input, specifier):
    parameter, flag = 0, 0
    while flag == 0:
        try:
            if specifier:
                parameter = int(input(message_input))
            else:
                parameter = float(input(message_input))

            flag = 1
        except:
            print("[!]Error. Number should be entered. Try again.")

    return parameter


def method_1(n):
    s_method1 = 0
    x_current = x_start
    step = (x_end - x_start) / n

    while abs(x_end - x_current) > eps:
        s_method1 += function(x_current) * step
        x_current += step

    return s_method1


def method_2(n):
    s_method2 = 0
    step = (x_end - x_start) / n
    x_prev = x_start
    x_current = x_start + step

    while abs(x_end - x_current) > eps:
        s_method2 += (function(x_prev) + 3 * function((2 * x_prev + x_current) / 3) + 3 * function(
            (x_prev + 2 * x_current) / 3) + function(x_current)) / 8 * step
        x_prev = x_current
        x_current += step

    return s_method2


# Input block
x_start = input_checking_errors("Enter start of the segment: ", 0)
x_end = input_checking_errors("Enter end of the segment: ", 0)

while x_end <= x_start:
    x_end = input_checking_errors("Enter end of the segment: ", 0)

n1_segments = input_checking_errors("Enter first number of segments to divide on: ", 1)
n2_segments = input_checking_errors("Enter second number of segments to divide on: ", 1)


# Computing block
eps = 1e-10

# Left rectangles
sum_v1_n1 = method_1(n1_segments)
sum_v1_n2 = method_1(n2_segments)

# 3/8
sum_v2_n1 = method_2(n1_segments)
sum_v2_n2 = method_2(n2_segments)

print("┌─────────────┬──────────────────────┬──────────────────────┐")
print("│             │          N1          │          N2          │")
print("├─────────────┼──────────────────────┼──────────────────────┤")
print("│  Method #1  │" + " {:20.5g} ".format(sum_v1_n1) + "│" + " {:20.5g} ".format(sum_v1_n2) + "│")
print("├─────────────┼──────────────────────┼──────────────────────┤")
print("│  Method #2  │" + " {:20.5g} ".format(sum_v2_n1) + "│" + " {:20.5g} ".format(sum_v2_n2) + "│")
print("└─────────────┴──────────────────────┴──────────────────────┘")

expected = antiderivative_function(x_end) - antiderivative_function(x_start)
print("Expected value is: {:.7g}".format(expected))

absolute_v1_n1 = sum_v1_n1 - expected
absolute_v1_n2 = sum_v1_n2 - expected
absolute_v2_n1 = sum_v2_n1 - expected
absolute_v2_n2 = sum_v2_n2 - expected

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
print("│  Method #2  │" + " {:14.7g} ".format(absolute_v2_n1) + "│" + " {:14.7g} ".format(relative_v2_n1) + "│" +
      " {:14.7g} ".format(absolute_v2_n2) + "│" + " {:14.7g} ".format(relative_v2_n2) + "│")
print("└─────────────┴────────────────┴────────────────┴────────────────┴────────────────┘")

most_precise_method = 1 if abs(absolute_v1_n1) < abs(absolute_v2_n1) else 2
print("The most precise is method #{:g}".format(most_precise_method))

eps_entered = input_checking_errors("Enter eps to compute: ", 0)

n = 1
if most_precise_method == 1:
    while abs(method_2(n) - method_2(n * 2)) >= eps_entered:
        n += 1
else:
    while abs(method_1(n) - method_1(n * 2)) >= eps_entered:
        n += 1

print("Number of segments needed is {:.7g}".format(n))
