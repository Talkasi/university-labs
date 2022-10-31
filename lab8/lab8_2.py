# Kuracheva K.D., ИУ7-13Б
'''
2. Переставить местами строки с наибольшим и наименьшим количеством
отрицательных элементов.
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
max_counter = -1
needed_min_line_i = -1
needed_max_line_i = -1
for i in range(m):
    counter = 0
    for j in range(n):
        if list_n[i][j] < 0:
            counter += 1

    if counter < min_counter:
        min_counter = counter
        needed_min_line_i = i

    if counter > max_counter:
        max_counter = counter
        needed_max_line_i = i

list_n[needed_max_line_i], list_n[needed_min_line_i] = list_n[needed_min_line_i], list_n[needed_max_line_i]

print("\nNew matrix is:")
for i in range(m):
    s = ""
    for j in list_n[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)
