# Kuracheva K. D., ИУ7-13Б
'''
Подсчитать в каждой строке матрицы D количество элементов, превышающих
суммы элементов соответствующих строк матрицы Z.

Разместить эти количества в массиве G, умножить матрицу D на максимальный элемент массива G.
Напечатать матрицу Z, матрицу D до и после преобразования, а также массив G
'''

print("Enter parameters for matrix D:")
m, n = map(int, input("Enter number of lines, columns: ").split())
d = [[0.0] * n for i in range(m)]

for i in range(m):
    print("New line: ")
    for j in range(n):
        d[i][j] = float(input("Enter element in line {:g}, column {:g}: ".format(j + 1, i + 1)))

print("\nEntered matrix D is:")
for i in range(m):
    s = ""
    for j in d[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)

print("Enter parameters for matrix F:")
nz = int(input("Enter number of columns: "))
z = [[0.0] * nz for i in range(m)]

for j in range(nz):
    print("New column:")
    for i in range(m):
        z[i][j] = float(input("Enter element in line {:g}, column {:g}: ".format(i + 1, j + 1)))

print("Entered matrix Z is: ")
for i in range(m):
    s = ""
    for elem in z[i]:
        s += " {:7.7g} ".format(elem)
    print(s)

g = [0] * m
for i_z in range(m):
    s_zline = 0
    for j_z in range(nz):
        s_zline += z[i_z][j_z]

    for j in range(n):
        g[i_z] += 1 if d[i_z][j] > s_zline else 0

for i in range(m):
    for j in range(n):
        d[i][j] *= max(g)


print("\nNew matrix D is:")
for i in range(m):
    s = ""
    for j in d[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)

print("List G: ")
s = ""
for i in range(m):
    s += "  {:7.7g}   ".format(g[i])
print(s)
