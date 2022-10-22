# Kuracheva K.D., ИУ7-13Б
# Delete all positive elements in the list by one loop

n = int(input("Enter number of elements in the list: "))
list_n = [0] * n

for i in range(n):
    list_n[i] = int(input("Enter element #{:g}: ".format(i + 1)))

s_positive_index = -1
for i in range(n):
    if list_n[i] <= 0 and s_positive_index != -1:
        list_n[s_positive_index] = list_n[i]
        s_positive_index += 1
    else:
        if list_n[i] > 0:
            s_positive_index = i if s_positive_index == -1 else s_positive_index

list_n = list_n[:s_positive_index]
print("\nNew list is:")
for i in range(s_positive_index):
    print("#{:g}: {:g}".format(i + 1, list_n[i]))
