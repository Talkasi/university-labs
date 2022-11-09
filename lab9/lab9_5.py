# Kuracheva K. D., ИУ7-13Б
# Task: Replace all english vowels by points in symbolic matrix.

n, m = map(int, input("Enter number of columns, lines: ").split())
list_n = [[''] * n for i in range(m)]

for i in range(n):
    print("New column: ")
    for j in range(m):
        list_n[j][i] = str(input("Enter symbol in line {:g}, column {:g}: ".format(j + 1, i + 1)))

        # If an error occurred
        while len(list_n[j][i]) != 1:
            print("Length of the element should be 1. Try again.")
            list_n[j][i] = str(input("Enter element in line {:g}, column {:g}: ".format(j + 1, i + 1)))

print("\nEntered matrix is:")
for i in range(m):
    s = ""
    for j in list_n[i]:
        s += "  {:5s}   ".format(j)
    print(s)

# Replacing vowels by points
for j in range(n):
    for i in range(m):
        if list_n[i][j] in "aeyuio":
            list_n[i][j] = '.'

print("\nNew matrix is:")
for i in range(m):
    s = ""
    for j in list_n[i]:
        s += "  {:5s}   ".format(j)
    print(s)
