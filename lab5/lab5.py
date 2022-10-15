# Kuracheva K.D., ИУ7-13Б
# Computes sum of the function V70
import math

x = float(input("Enter x: "))
eps = abs(float(input("Enter eps: ")))
iterations_max = int(input("Enter max number of iterations: "))
while iterations_max <= 0:
    iterations_max = int(input("This number shouldn't be less then 1.\nEnter max number of iterations: "))

step = int(input("Enter step for table to print: "))
while step <= 0:
    step = int(input("This number shouldn't be less then 1.\nEnter step for table to print: "))

# Print a table of values for the function
print("┌───────────┬────────────────────────┬────────────────────────┐")
print("│     #     │      Current term      │      Current sum       │")
print("├───────────┼────────────────────────┼────────────────────────┤")

n = 1
s_previous = math.inf
s_current = x
t_current = x
print("│_{:9d} │_ {:20.7g}  │_ {:20.7g}  │".format(n, t_current, s_current))

while n < iterations_max and abs(t_current) > eps:
    n += 1
    s_previous = s_current

    # Hacking overflow error
    t_current = (-t_current) * x ** 2 * (2 * (n - 1) + 1) / (2 * n + 1)

    s_current = s_previous + t_current

    # Print the values for the table
    if (n - 1) % step == 0:
        print("│_{:9d} │_ {:20.7g}  │_ {:20.7g}  │".format(n, t_current, s_current))

    # Error check
    if math.isnan(s_current) or math.isinf(s_current):
        break

print("└───────────┴────────────────────────┴────────────────────────┘")

# Answer output block
if math.isnan(s_current) or math.isinf(s_current):
    print("Error. The value of the sum is too big to compare it with given eps.")
elif n == iterations_max and abs(t_current) > eps:
    print("Number of max iterations is not enough to compute the sum.")
else:
    print("The sum is {:.7g}, it was computed by {:d} iterations.".format(s_current, n))
