# Kuracheva K.D., ИУ7-13Б
# Change all upper english characters to the lower ones in the list of strings
from soupsieve.util import lower

n = int(input("Enter number of elements in the list: "))
list_n = [""] * n

for i in range(n):
    list_n[i] = str(input("Enter element #{:g}: ".format(i + 1)))

# Change all upper english characters to the lower ones in each string
for i in range(n):
    list_n[i] = lower(list_n[i])

print("\nNew list is:")
for i in range(n):
    print("#{:g}: {:s}".format(i + 1, list_n[i]))
