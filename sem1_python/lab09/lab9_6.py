# Kuracheva K. D., ИУ7-13Б
'''
Сформировать матрицу C путём построчного перемножения матриц A и B
одинаковой размерности (элементы в i-й строке матрицы A умножаются на
соответствующие элементы в i-й строке матрицы B), потом сложить все
элементы в столбцах матрицы C и записать их в массив V. Напечатать матрицы
A, B, C и массив V.
'''
n, m = map(int, input("Enter number of lines, columns of matrix A and B: ").split())

# Checking for input errors
while n < 1:
    print("[!]Error. Number of lines should be bigger than 0. Try again.")
    n = int(input("Enter number of lines: "))

while m < 1:
    print("[!]Error. Number of columns should be bigger than 0. Try again.")
    m = int(input("Enter number of columns: "))

a = [[0.0] * m for i in range(n)]
b = [[0.0] * m for i in range(n)]

print("\nStart working with matrix A.")
for j in range(m):
    print("New column")
    for i in range(n):
        a[i][j] = float(input("Matrix A: Enter element in line {:g}, column {:g}: ".format(i + 1, j + 1)))

print("Entered matrix A:")
for j in range(m):
    s = ""
    for i in range(n):
        s += " {:10.7g} ".format(a[i][j])

    print(s)

print("\nStart working with matrix B.")
for j in range(m):
    print("New column")
    for i in range(n):
        b[i][j] = float(input("Matrix B: Enter element in line {:g}, column {:g}: ".format(i + 1, j + 1)))

print("Entered matrix B:")
for j in range(m):
    s = ""
    for i in range(n):
        s += " {:10.7g} ".format(b[i][j])

    print(s)

print("\nStart working with matrix C.")
c = [[0.0] * m for i in range(n)]

for j in range(m):
    for i in range(n):
        c[i][j] = a[i][j] * b[i][j]

print("Matrix C:")
for j in range(n):
    s = ""
    for i in range(m):
        s += " {:10.7g} ".format(c[i][j])

    print(s)

v = []
for j in range(m):
    s = 0
    for i in range(n):
        s += c[i][j]

    v.append(s)

print("List V:")
for j in range(len(v)):
    print("Element #{:g}: {:g}".format(j + 1, v[j]))
