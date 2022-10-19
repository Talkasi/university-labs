# Kuracheva K.D., ИУ7-13Б
# Exchange min even element and max odd
from math import inf, isinf

n = int(input("Enter number of elements in the list: "))
list_n = [0] * n

for i in range(n):
    list_n[i] = int(input("Enter element #{:g}: ".format(i + 1)))

min_even_i, max_odd_i = 0, 0
min_even, max_odd = inf, -inf

for i in range(n):
    if list_n[i] % 2 == 0 and list_n[i] < min_even:
        min_even = list_n[i]
        min_even_i = i

    if list_n[i] % 2 == 1 and list_n[i] > max_odd:
        max_odd = list_n[i]
        max_odd_i = i


if isinf(min_even) or isinf(max_odd):
    print("\nThere is not enough parameters to exchange.")
else:
    list_n[max_odd_i], list_n[min_even_i] = min_even, max_odd
    print("\nMin even is {:g}, max odd is {:g}".format(min_even, max_odd))

    print("\nChanged list is:")
    for i in range(n):
        print("#{:g}: {:g}".format(i + 1, list_n[i]))
