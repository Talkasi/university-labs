# Kuracheva K.D., ИУ7-13Б
# Insert 2a after each a in the list if a is negative not using loop in the loop

n = int(input("Enter number of elements in the list: "))
list_n = [0] * n

for i in range(n):
    list_n[i] = int(input("Enter element #{:g}: ".format(i + 1)))

c_negative = 0
for i in range(n):
    if list_n[i] < 0:
        c_negative += 1
        list_n.append(0)

step = c_negative
for i in range(n - 1, -1, -1):
    if list_n[i] >= 0:
        list_n[i + step] = list_n[i]
    else:
        list_n[i + step] = 2 * list_n[i]
        step -= 1
        list_n[i + step] = list_n[i]

print("\nNew list is:")
for i in range(n + c_negative):
    print("#{:g}: {:g}".format(i + 1, list_n[i]))
