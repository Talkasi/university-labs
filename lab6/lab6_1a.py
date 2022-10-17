# Kuracheva K.D., ИУ7-13Б
# Add an element to a given location in a list (by index) using
# any Python tools

n = int(input("Enter number of elements in the list: "))
list_n = [0] * n

for i in range(n):
    list_n[i] = int(input("Enter element #{:g}: ".format(i + 1)))

# k is the index of the element to add, but user writes the position of this element, so the value is decreased
k = int(input("\nEnter position to add an element in (from 1 to {:g}): ".format(n + 1))) - 1
while k > n:
    k = int(input("\n[!]Error. You can't add an element on the position > n + 1."
                  "\nEnter position to add an element in: ")) - 1

el = int(input("Enter an element to add into a list: "))

list_n.insert(k, el)

n += 1
print("\n[+]Task was successfully completed.\nNew list:")
for i in range(n):
    print("#{:g}: {:g}".format(i + 1, list_n[i]))
