# Kuracheva K.D., ИУ7-13Б
'''
1. Найти строку, имеющую определённое свойство по варианту.
Варианты к п. 1:
4. Наименьшее количество чётных элементов.
'''
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

min_counter = m * n
needed_line_i = -1
for i in range(m):
    counter = 0
    for j in range(n):
        if list_n[i][j] % 2 == 0:
            counter += 1

    if counter < min_counter:
        min_counter = counter
        needed_line_i = i

print("\nNeeded line is:")
s = ""
for j in list_n[needed_line_i]:
    s += "  {:7.7g}   ".format(j)
print(s)
