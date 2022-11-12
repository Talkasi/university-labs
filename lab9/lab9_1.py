# Kuracheva K. D., ИУ7-13Б
'''
Даны массивы D и F. Сформировать матрицу A по формуле
ajk = sin(dj+fk).
Определить среднее арифметическое положительных чисел каждой строки
матрицы и количество элементов, меньших среднего арифметического.
Результаты записать соответственно в массивы AV и L. Напечатать матрицу A в
виде матрицы и рядом столбцы AV и L.
'''
from math import sin

# Enter parameters for list D
md = int(input("Enter number of elements in list D: "))
while md < 1:
    print("Error. Number of elements should be bigger then 0. Try again.")
    md = int(input("Enter number of elements in list D: "))

d = [0.0] * md
for i in range(md):
    d[i] = float(input("Enter element #{:g}: ".format(i + 1)))

print("\nList D:")
for i in range(md):
    print("#{:g}: {:.7g} ".format(i + 1, d[i]))


# Enter parameters for list F
nf = int(input("\nEnter number of elements in list F: "))
while nf < 1:
    print("Error. Number of elements should be bigger then 0. Try again.")
    nf = int(input("Enter number of elements in list F: "))

f = [0.0] * nf
for i in range(nf):
    f[i] = float(input("Enter element #{:g}: ".format(i + 1)))

print("\nList F:")
for i in range(nf):
    print("#{:g}: {:.7g} ".format(i + 1, f[i]))

# New matrix:
a = [[0.0] * nf for i in range(md)]
av = [0.0] * md

for i in range(md):
    count = 0
    
    for j in range(nf):
        a[i][j] = sin(d[i] + f[j])
        if a[i][j] > 0:
            av[i] += a[i][j]
            count += 1
        
    av[i] = av[i] / count if count != 0 else 0

l = [0.0] * md
for i in range(md):
    for j in range(nf):
        if a[i][j] < av[i]:
            l[i] += 1


print("\n" + "Matrix A ".center(17 * nf) + "AV".center(19) + "L".center(17) + "\n")
for i in range(md):
    s = "|"
    for elem in a[i]:
        s += " {:15.7g} ".format(elem)
    print(s + "| {:15.7g} | {:15.7g} |".format(av[i], l[i]))
