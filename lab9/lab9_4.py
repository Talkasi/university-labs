# Kuracheva K. D., ИУ7-13Б
'''
Задана матрица D и массив I, содержащий номера строк, для которых
необходимо определить максимальный элемент. Значения максимальных
элементов запомнить в массиве R. Определить среднее арифметическое
вычисленных максимальных значений. Напечатать матрицу D, массивы I и R,
среднее арифметическое значение.
'''

print("Enter parameters for matrix D:")
m, n = map(int, input("Enter number of lines, columns: ").split())
d = [[0.0] * n for i in range(m)]

for i in range(m):
    print("New line: ")
    for j in range(n):
        d[i][j] = float(input("Enter element in line {:g}, column {:g}: ".format(i + 1, j + 1)))

print("\nEntered matrix D is:")
for i in range(m):
    s = ""
    for j in d[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)

print("Enter parameters for list I: ")
pari = int(input("Enter number of elements in the list: "))
while pari < 1:
    print("[!]Error. Number of elements should be bigger than 0")

i = [0] * pari
for index in range(pari):
    i[index] = int(input("Enter element #{:g}: ".format(index + 1)))
    while 1 > i[index] or i[index] > m:
        print(
            "[!]Error. Element is a number of a line, so "
            "it should be bigger than 0 and less than {:g}. Try again.".format(m + 1))
        i[index] = int(input("Enter element #{:g}: ".format(index + 1)))

print("List I:")
for j in range(len(i)):
    print("Element #{:g}: {:g}".format(j + 1, i[j]))

r = []
for j in i:
    r.append(max(d[j - 1]))

print("List R:")
for j in range(len(r)):
    print("Element #{:g}: {:g}".format(j + 1, r[j]))

sum_by_n = sum(r) / len(r)
print("Sum / n = {:.7g}".format(sum_by_n))
