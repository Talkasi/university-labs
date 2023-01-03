def f(x):
    return x


def a_F(x):
    return x ** 2 / 2


def s_method(n):
    step = abs(x_end - x_start) / n
    x_curr = x_start
    s = 0

    for i in range(n):
        s += (f(x_curr) + f(x_curr + step)) / 2 * step
        x_curr += step

    return s


def input_errors_checking(message, dtype):
    parameter = 0
    number_not_entered = 1
    while number_not_entered:
        try:
            if dtype:
                parameter = float(input(message))
                number_not_entered = 0
            else:
                parameter = int(input(message))
                number_not_entered = 0
        except:
            print("[!]Error. Number of type " + ("float" if dtype else "int") + " is expected. Try again.")

    return parameter


float_type = 1
int_type = 0

x_start = input_errors_checking("Enter x_start of the segment: ", float_type)
x_end = input_errors_checking("Enter x_end of the segment: ", float_type)

if x_start > x_end:
    x_start, x_end = x_end, x_start

n = input_errors_checking("Enter number of segments to divibe on: ", int_type)

while n < 1:
    print("[!]Error. Number of segments should be bigger then 0. Try again.")
    n = input_errors_checking("Enter number of segments to divibe on: ", int_type)

print("\nS counted by given method is: {:.7g}".format(s_method(n)))
print("S excpected: {:.7g}".format(abs(a_F(x_end) - a_F(x_start))))
