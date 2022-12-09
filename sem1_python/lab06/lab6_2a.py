# Kuracheva K.D., ИУ7-13Б
# Delete an element to a given location in a list (by index) using
# any Python tools

n = int(input("Enter number of elements in the list: "))
list_n = [0] * n

for i in range(n):
    list_n[i] = int(input("Enter element #{:g}: ".format(i + 1)))

# k is the index of the element to delete, but user writes the position of this element, so the value is decreased
k = int(input("\nEnter position to delete an element from (from 1 to {:g}): ".format(n))) - 1

while k < 0 or k >= n:
    k = int(input("\n[!]Error. You can't delete an element from the position p (0 < p < n)."
                  "\nEnter position to delete an element from (from 1 to {:g}): ".format(n))) - 1

list_n.pop(k)

n -= 1
print("\n[+]Task was successfully completed.\nNew list:")
for i in range(n):
    print("#{:g}: {:g}".format(i + 1, list_n[i]))
