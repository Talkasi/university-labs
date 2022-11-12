# Kuracheva K. D., ИУ7-13Б
'''
Подсчитать в каждой строке матрицы D количество элементов, превышающих
суммы элементов соответствующих строк матрицы Z.

Разместить эти количества в массиве G, умножить матрицу D на максимальный элемент массива G.
Напечатать матрицу Z, матрицу D до и после преобразования, а также массив G
'''

print("Enter parameters for matrix D:")
n, m = map(int, input("Enter number of lines, columns: ").split())

# Checking for input errors
while n < 1:
    print("[!]Error. Number of lines should be bigger than 0. Try again.")
    n = int(input("Enter number of lines: "))

while m < 1:
    print("[!]Error. Number of columns should be bigger than 0. Try again.")
    m = int(input("Enter number of columns: "))

d = [[0.0] * m for i in range(n)]

for i in range(n):
    print("New line: ")
    for j in range(m):
        d[i][j] = float(input("Enter element in line {:g}, column {:g}: ".format(i + 1, j + 1)))

print("\nEntered matrix D is:")
for i in range(n):
    s = ""
    for j in d[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)

print("Enter parameters for matrix Z. Number of lines of matrix F = number of lines of matrix D")
mz = int(input("Enter number of columns: "))
z = [[0.0] * mz for i in range(n)]

for i in range(n):
    print("New column:")
    for j in range(mz):
        z[i][j] = float(input("Enter element in line {:g}, column {:g}: ".format(i + 1, j + 1)))

print("Entered matrix Z is: ")
for i in range(n):
    s = ""
    for elem in z[i]:
        s += " {:7.7g} ".format(elem)
    print(s)

g = [0] * n
for i_z in range(n):
    s_zline = 0
    for j_z in range(mz):
        s_zline += z[i_z][j_z]

    for j in range(m):
        g[i_z] += 1 if d[i_z][j] > s_zline else 0

max_el = max(g)
for i in range(n):
    for j in range(m):
        d[i][j] *= max_el


print("\nNew matrix D is:")
for i in range(n):
    s = ""
    for j in d[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)

print("List G: ")
for i in range(n):
    print("#{:g}: {:.7g}".format(i + 1, g[i]))
