# Kuracheva K.D., ИУ7-13Б, V70
import math

x = float(input("Enter x: "))
eps = float(input("Enter eps: "))
iterations_max = float(input("Enter max number of iterations: "))
step = float(input("Enter step for table to print: "))

# Print a table of values for the function
print("┌───────────┬────────────────────────┬────────────────────────┐")
print("│     #     │      Current term      │      Current sum       │")
print("├───────────┼────────────────────────┼────────────────────────┤")

n = 1
s_previous = math.inf
s_current = x
t_current = x
print("│_{:9d} │_ {:20.7g}  │_ {:20.7g}  │".format(n, t_current, s_current))

while n < iterations_max and abs(s_previous - s_current) >= eps:
    s_previous = s_current

    # Hacking overflow error
    k = 0
    t_current = (-1) ** n / (2 * n + 1)
    while k != 2 * n + 1:
        t_current *= x
        k += 1

    s_current = s_previous + t_current

    # Print the values for the table
    n += 1
    if n % step == 1:
        print("│_{:9d} │_ {:20.7g}  │_ {:20.7g}  │".format(n, t_current, s_current))

    # Error check
    if math.isnan(s_current):
        break

print("└───────────┴────────────────────────┴────────────────────────┘")

# Answer output block
if math.isnan(s_current):
    print("Error. The value of the sum is too big to compare it with given eps.")
elif n == iterations_max and abs(s_previous - s_current) >= eps:
    print("Number of max iterations is not enough to compute the sum.")
else:
    print("The sum is {:.7g}, it was computed by {:d} iterations.".format(s_current, n))
