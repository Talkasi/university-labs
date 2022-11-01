# Kuracheva K.D., ИУ7-13Б
import math
m, n = map(int, input("Enter number of elements in the list: ").split())
list_n = [[0.0] * n for i in range(m)]

for i in range(m):
    print("New line goes: ")
    for j in range(n):
        list_n[i][j] = float(input("Enter element}: "))

print("\nEntered matrix is:")
for i in range(m):
    s = ""
    for j in list_n[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)

min_sum = math.inf
max_sum = -math.inf
needed_min_column_j = -1
needed_max_column_j = -1

for j in range(n):
    s = sum(list_n[i][j] for i in range(m))

    if s < min_sum:
        min_sum = s
        needed_min_column_j = j

    if s > max_sum:
        max_sum = s
        needed_max_column_j = j

for i in range(m):
    list_n[i][needed_min_column_j], list_n[i][needed_max_column_j] = list_n[i][needed_max_column_j], list_n[i][
        needed_min_column_j]

print("\nNew matrix is:")
for i in range(m):
    s = ""
    for j in list_n[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)
