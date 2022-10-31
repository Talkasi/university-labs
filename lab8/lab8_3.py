# Kuracheva K.D., ИУ7-13Б
'''
3. Найти столбец, имеющий определённое свойство по варианту.
Варианты к п. 3:
5. Наибольшее количество чисел, являющихся степенями 2
'''
m, n = map(int, input("Enter number of elements in the list: ").split())
list_n = [[0] * n for i in range(m)]

for i in range(m):
    print("New line goes: ")
    for j in range(n):
        list_n[i][j] = int(input("Enter element}: "))

print("\nEntered matrix is:")
for i in range(m):
    s = ""
    for j in list_n[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)

max_counter = -1
needed_max_line_i = -1
for j in range(n):
    counter = 0
    for i in range(m):
        if bin(list_n[i][j])[2:].count('1') == 1:
            counter += 1

    if counter > max_counter:
        max_counter = counter
        needed_max_line_i = j

print("\nNeeded column is:")
for k in range(m):
    print("  {:7.7g}   ".format(list_n[k][needed_max_line_i]))
