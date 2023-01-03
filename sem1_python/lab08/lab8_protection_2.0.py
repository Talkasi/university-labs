# Максимум - ? Обнулить строки и столбцы на пересеч которых находятся все вхождения максимума

from math import inf

n, m = map(int, input("Enter lines, columns of matrix: ").split())

list_n = [[0.0] * m for i in range(n)]
for i in range(n):
    print("New line")
    for j in range(m):
        list_n[i][j] = float(input("Element in line {:g}, column {:g}: ".format(i + 1, j + 1)))

print("Entered matrix is:")
for i in range(n):
    s = ""
    for j in range(m):
        s += " {:7.5g} ".format(list_n[i][j])

    print(s)

max_el = -inf
for i in range(n):
    for j in range(m):
        if max_el < list_n[i][j]:
            max_el = list_n[i][j]

print("Maximum of this matrix is {:7.5g}".format(max_el))
columns_to_null = set()
lines_to_null = set()
for i in range(n):
    for j in range(m):
        if list_n[i][j] == max_el:
            columns_to_null.add(j)
            lines_to_null.add(i)

for i in lines_to_null:
    for k in range(m):
        list_n[i][k] = 0

for j in columns_to_null:
    for k in range(n):
        list_n[k][j] = 0

print("Changed matrix is:")
for i in range(n):
    s = ""
    for j in range(m):
        s += " {:7.5g} ".format(list_n[i][j])

    print(s)
