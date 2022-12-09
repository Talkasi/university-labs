# Kuracheva K.D., ИУ7-13Б
# Find the value of the k-th point of extreme in the list

n = int(input("Enter number of elements in the list: "))
list_n = [0] * n

for i in range(n):
    list_n[i] = int(input("Enter element #{:g}: ".format(i + 1)))

# k is the number of extremum to find
k = int(input("\nEnter a number of a point of extreme to find (from 1 to {:g}): ".format(n - 2)))

while k < 1 or k > n - 2:
    k = int(input("\n[!]Error. This value can't be a real number of the point of extreme."
                  "\nEnter a number of a point of extreme to find (from 1 to {:g}): ".format(n - 2)))

c_extremums = 0
for i in range(1, n - 1):
    if list_n[i - 1] < list_n[i] > list_n[i + 1] or list_n[i - 1] > list_n[i] < list_n[i + 1]:
        c_extremums += 1

    if c_extremums == k:
        print("\nThe value of the k-th point of extreme is {:g}.".format(list_n[i]))
        break
else:
    print("\nThis list doesn't contain a point of extreme with a given number. "
          "\nIt has {:g} point(s) of extreme.".format(c_extremums))
