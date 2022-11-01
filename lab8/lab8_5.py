# Kuracheva K.D., ИУ7-13Б
import math
n = int(input("Enter number of elements in the list: "))
list_n = [[0.0] * n for i in range(n)]

for i in range(n):
    print("New line goes: ")
    for j in range(n):
        list_n[i][j] = float(input("Enter element}: "))

print("\nEntered matrix is:")
for i in range(n):
    s = ""
    for j in list_n[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)

max_el, min_el = - math.inf, math.inf
for i in range(n):
    counter = 0
    for j in range(n):
        if i < j:
            max_el = max(max_el, list_n[i][j])

        if n - 1 - i < j:
            min_el = min(min_el, list_n[i][j])


print("Max_el is {:.7g}".format(max_el))
print("Min_el is {:.7g}".format(min_el))
