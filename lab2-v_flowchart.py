# Write a solver to: a * x**2 + b * x + c = 0
print('\tInput area <-> Data\n')
a = float(input("Enter the first parameter (a): "))
b = float(input("Enter the second parameter (b): "))
c = float(input("Enter the third parameter (c): "))

print('\n\tOutput area <-> Result')
if a == 0:  # Special cases
    if b == 0:
        if c == 0:
            print("\nx can be any value.")
        else:
            print("\nThere is no solution.")  # there is no x solving it
    else:
        x = -c / b
        print("\nThe answer is {:.7g}.".format(x))
else:
    d = b ** 2 - 4 * a * c  # discriminant
    if d < 0:
        print("\nThere is no solution.")  # there is no x solving it
    elif d == 0:
        x = -b / 2 / a
        print("\nThere is one solution: {:.7g}.".format(x))
    else:
        x1 = (-b + d ** 0.5) / 2 / a
        x2 = (-b - d ** 0.5) / 2 / a
        print("\nThere are two solutions: {:.7g} and {:.7g}.".format(x1, x2))
