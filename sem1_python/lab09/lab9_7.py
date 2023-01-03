# Kuracheva K. D., ИУ7-13Б
'''
Ввести трёхмерный массив (массив матриц размера X*Y*Z), вывести из него i-й
срез (матрицу - фрагмент трёхмерного массива) по второму индексу (нумерация
индексов начинается с 1).
'''

x, y, z = map(int, input("Enter parameters of matrix (x, y, z), separated by space: ").split())

# Checking for input errors
while x < 1:
    print("[!]Error. Number of lines should be bigger than 0. Try again.")
    x = int(input("Enter number of lines: "))

while y < 1:
    print("[!]Error. Number of columns should be bigger than 0. Try again.")
    y = int(input("Enter number of columns: "))

while z < 1:
    print("[!]Error. Width of matrix should be bigger than 0. Try again.")
    z = int(input("Enter width of matrix: "))

matrix = [[[0.0] * y for i in range(x)] for j in range(z)]
print(matrix)
for k in range(z):
    print()
    for j in range(y):
        for i in range(x):
            matrix[k][i][j] = float(
                input("Enter element #: z = {:g}, x = {:g}, y = {:g}: ".format(k + 1, i + 1, j + 1)))

index = int(input("\nEnter second index to complete the task: "))

# Checking for input errors
while index < 1 or index > y:
    print("[!]Error. Index should be bigger than 0 and less than {:g}. Try again.".format(y))
    index = int(input("Enter 2nd index of matrix: "))

index -= 1

for j in range(z):
    s = ""
    for i in range(x):
        s += " {:15.7g} ".format(matrix[j][i][index])

    print(s)
