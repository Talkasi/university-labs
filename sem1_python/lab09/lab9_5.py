# Kuracheva K. D., ИУ7-13Б
# Task: Replace all english vowels by points in symbolic matrix.

n, m = map(int, input("Enter number of lines, columns: ").split())

# Checking for input errors
while n < 1:
    print("[!]Error. Number of lines should be bigger than 0. Try again.")
    n = int(input("Enter number of lines: "))

while m < 1:
    print("[!]Error. Number of columns should be bigger than 0. Try again.")
    m = int(input("Enter number of columns: "))

list_n = [[''] * m for i in range(n)]

for i in range(n):
    print("New line: ")
    for j in range(m):
        list_n[i][j] = str(input("Enter symbol in line {:g}, column {:g}: ".format(i + 1, j + 1)))

        # If an error occurred
        while len(list_n[i][j]) != 1:
            print("Length of the element should be 1. Try again.")
            list_n[i][j] = str(input("Enter element in line {:g}, column {:g}: ".format(i + 1, j + 1)))

print("\nEntered matrix is:")
for i in range(n):
    s = ""
    for j in list_n[i]:
        s += "  {:5s}   ".format(j)
    print(s)

# Replacing vowels by points
for i in range(n):
    for j in range(m):
        if list_n[i][j] in "aeyuio":
            list_n[i][j] = '.'

print("\nNew matrix is:")
for i in range(n):
    s = ""
    for j in list_n[i]:
        s += "  {:5s}   ".format(j)
    print(s)
