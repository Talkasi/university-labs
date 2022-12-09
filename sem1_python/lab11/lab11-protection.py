'''
Quick sort
'''


def input_errors_checking(message, dtype):
    while True:
        try:
            if dtype == "float":
                parameter = float(input(message))
            elif dtype == "int":
                parameter = int(input(message))
            else:
                parameter = 0
                print("[!]Error. Wrong type - function supports int and float. 0 returned.")

            return parameter
        except:
            print("[!]Error. Number of type {:s} should be entered".format(dtype))


def quick_sort(given_list):
    if len(given_list) < 2:
        return given_list
    else:
        current_element = given_list[len(given_list) // 2]
        lower_numbers = []
        equal_numbers = []
        bigger_numbers = []
        for index in range(len(given_list)):
            if given_list[index] < current_element:
                lower_numbers.append(given_list[index])
            elif given_list[index] == current_element:
                equal_numbers.append(given_list[index])
            else:
                bigger_numbers.append(given_list[index])

        return quick_sort(lower_numbers) + equal_numbers + quick_sort(bigger_numbers)


n = input_errors_checking("Enter number of elements in the list: ", "int")

while n < 1:
    print("[!]Error. Number of elements should be bigger then 0. Try again.")
    n = input_errors_checking("Enter number of elements in the list: ", "int")


a = [0.0] * n

for i in range(n):
    a[i] = input_errors_checking("Enter element #{:g}: ".format(i + 1), "float")

print("\nEntered list")
for i in range(n):
    print("Element #{:g}: {:.7g}".format(i + 1, a[i]))


sorted_list = quick_sort(a)


print("\nSorted list.")
for i in range(n):
    print("Element #{:g}: {:.7g}".format(i + 1, sorted_list[i]))
