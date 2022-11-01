# Kuracheva K.D., ИУ7-13Б
n = int(input("Enter number of elements in the list: "))
list_n = [[0.0] * n for i in range(n)]

for i in range(n):
    print("New line goes: ")
    for j in range(n):
        list_n[i][j] = float(input("Enter element}: "))

print("\nEntered matrix is:")
for i in range(n):
    s = ""
    for j in list_n[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)

for i in range(n):
    for j in range(n):
        if i > j:
            list_n[i][j], list_n[j][i] = list_n[j][i], list_n[i][j]

print("\nNew matrix is:")
for i in range(n):
    s = ""
    for j in list_n[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)
