# Kuracheva K. D., ИУ7-13Б
'''
Повернуть квадратную целочисленную матрицу на 90 градусов по часовой
стрелке, затем на 90 градусов против часовой стрелки. Вывести исходную,
промежуточную и итоговую матрицы. Дополнительных матриц и массивов не
вводить. Транспонирование не применять.
'''

n = int(input("Enter number of lines and columns of a square matrix: "))

while n < 1:
    print("[!]Error. Number of lines and columns should be bigger than 0. Try again.")
    n = int(input("Enter number of lines and columns of a square matrix: "))

matrix = [[0.0] * n for i in range(n)]
for i in range(n):
    for j in range(n):
        matrix[i][j] = float(input("Enter element in line {:g}, column {:g}: ".format(i + 1, j + 1)))

print("Entered matrix is: ")
for j in range(n):
    s = ""
    for i in matrix[j]:
        s += "  {:7.7g}   ".format(i)
    print(s)

for i in range(n // 2):
    for j in range(i, n - i - 1):
        folder = matrix[i][j]
        matrix[i][j] = matrix[n - j - 1][i]
        matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j]
        matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i]
        matrix[j][n - 1 - i] = folder

print("Rotated 90 clockwise matrix is: ")
for i in range(n):
    s = ""
    for j in matrix[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)

for i in range(n // 2):
    for j in range(i, n - i - 1):
        folder = matrix[i][j]
        matrix[i][j] = matrix[j][n - 1 - i]
        matrix[j][n - 1 - i] = matrix[n - 1 - i][n - 1 - j]
        matrix[n - 1 - i][n - 1 - j] = matrix[n - 1 - j][i]
        matrix[n - 1 - j][i] = folder

print("Final matrix is: ")
for i in range(n):
    s = ""
    for j in matrix[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)
