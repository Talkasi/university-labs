# Write a solver to: a * x**2 + b * x + c = 0
print('\tInput area <-> Data\n')
a = float(input("Enter the first parameter (a): "))
b = float(input("Enter the second parameter (b): "))
c = float(input("Enter the third parameter (c): "))

print('\n\tOutput area <-> Result')
if a == 0:  # Special cases
    if b == 0 and c == 0:
        print("\nThe answer is infinity.")
    if b == 0 and c != 0:
        print("\nThere is no solution.")
    if b != 0:
        print("\nThe answer is {:.7g}.".format(-c / b))
else:
    d = b**2 - 4 * a * c
    if d < 0:
        print("\nThere is no solution.")
    elif d == 0:
        print("\nThere is one solution: {:.7g}.".format(-b / 2 / a if b != 0 else 0))
    else:
        print("\nThere are two solutions: {:.7g} and {:.7g}.".format((-b + d ** 0.5) / 2 / a, (-b - d ** 0.5) / 2 / a))

