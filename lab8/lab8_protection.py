# remove lines with 0s in matrix
n, m = map(int, input("Enter number of lines, number of columns, separated by spase: ").split())
list_n = [[0.0] * n for i in range(m)]

for i in range(m):
    print("New line of matrix: ")
    for j in range(n):
        list_n[i][j] = int(input("Enter element in line {:g}, column {:g}: ".format(i + 1, j + 1)))

print("\nEntered matrix is:")
for i in range(m):
    s = ""
    for j in list_n[i]:
        s += "  {:7.7g}   ".format(j)
    print(s)

i = 0
while i < len(list_n):
    if any(list_n[i][j] == 0 for j in range(n)):
        list_n.pop(i)
    else:
        i += 1

if len(list_n) == 0:
    print("Matrix is empty.")
else:
    print("New matrix is: ")
    for i in range(len(list_n)):
        s = ""
        for j in list_n[i]:
            s += "  {:7.7g}   ".format(j)
        print(s)

