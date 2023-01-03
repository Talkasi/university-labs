n = int(input("Enter parameter n (length = width) of matrix: "))

while n < 1:
    print("Error. n shoulb be bigger than 0. Try again.")
    n = int(input("Enter parameter n (length = width) of matrix: "))

a = [[0.0] * n for i in range(n)]

for i in range(n):
    print("New line")
    for j in range(n):
        a[i][j] = int(input("Matrix A: Enter element in line {:g}, column {:g}: ".format(i + 1, j + 1)))

print("Entered matrix")
for i in range(n):
    s = ""
    for j in a[i]:
        s += "{:15.7g}".format(j)
    print(s)

m = int(input("Enter parameter m (length) of the list: "))
k = int(m ** 0.5)

while k > n:
    print("Error. m is too big. Try again.")
    m = int(input("Enter parameter m (length) of the list: "))
    k = int(m ** 0.5)

b = [0.0] * m

for i in range(m):
    b[i] = int(input("List B: enter element #{:g}: ".format(i + 1)))

l = 0

for i in range(n - k, n):
    for j in range(k):
        a[i][j] = b[l]
        l += 1

print("New matrix")
for i in range(n):
    s = ""
    for j in a[i]:
        s += "{:15.7g}".format(j)
    print(s)
