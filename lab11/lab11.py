# Kuracheva K. D., ИУ7-13Б
import random
from time import time


def input_errors_checking(message, dtype):
    parameter = 0
    not_correct_input = 1
    while not_correct_input:
        try:
            if dtype:
                parameter = int(input(message))
            else:
                parameter = float(input(message))

            not_correct_input = 0
        except:
            print("[!]Error. Number " + ("(int)" if dtype else "(float)") + " should be entered. Try again.")

    return parameter


def insertion_with_barrier(given_list, length):
    permutations = 0
    time_spend_start = time()
    given_list = [0.0] + given_list

    for index in range(2, length + 1):
        if given_list[index - 1] > given_list[index]:
            given_list[0] = given_list[index]
            j = index - 1

            while given_list[j] > given_list[0] and j > 0:
                given_list[j + 1] = given_list[j]
                permutations += 1
                j -= 1

            given_list[j + 1] = given_list[0]

    given_list.pop(0)
    time_spend_end = time()
    return [given_list, time_spend_end - time_spend_start, permutations]


def create_list(elements_number, list_type):
    # list_type:
    #
    # random_list -> 0
    # sorted_list -> 1
    # reversed_sorted_list -> 2

    created_list = [0.0] * elements_number

    for index in range(elements_number):
        if list_type == 0:
            # random_list
            created_list[index] = random.randrange(-100, 100)

        elif list_type == 1:
            # sorted_list
            if index == 0:
                created_list[index] = random.randrange(-100, 100)
            else:
                created_list[index] = created_list[index - 1] + random.randrange(0, 100)

        elif list_type == 2:
            # reversed_sorted_list
            if index == 0:
                created_list[index] = random.randrange(-100, 100)
            else:
                created_list[index] = created_list[index - 1] - random.randrange(0, 100)
        else:
            print("[!]Error. Wrong list type.")
            break

    print("\nRandom " if list_type == 0 else "\nSorted " if list_type == 1 else "\nReversed_sorted ", end="")
    print("list with {:g} element(s):".format(elements_number))
    for index in range(elements_number):
        print("Element #{:g}: {:.7g}".format(index + 1, created_list[index]))

    return created_list


float_type = 0
int_type = 1

n = input_errors_checking("Enter number of elements in the list: ", int_type)

while n < 1:
    print("[!]Error. Number of elements should be bigger then 0. Try again.")
    n = input_errors_checking("Enter number of elements in the list: ", int_type)

a = [0.0] * n

for i in range(n):
    a[i] = input_errors_checking("Enter element #{:g}: ".format(i + 1), float_type)

print("\nEntered list:")
for i in range(n):
    print("Element #{:g}: {:.7g}".format(i + 1, a[i]))

a = insertion_with_barrier(a, n)[0]

print("\nSorted list:")
for i in range(n):
    print("Element #{:g}: {:.7g}".format(i + 1, a[i]))

# Part 2
number1_elements = input_errors_checking(
    "\nEnter 1st number of elements in the list to check time and number of permutations: ", int_type)

while number1_elements < 1:
    print("[!]Error. Number of elements should be bigger then 0. Try again.")
    number1_elements = input_errors_checking(
        "Enter 1st number of elements in the list to check time and number of permutations: ", int_type)

# Parameters for create_list() function
random_list = 0
sorted_list = 1
reversed_sorted_list = 2

random_n1 = create_list(number1_elements, random_list)
sorted_n1 = create_list(number1_elements, sorted_list)
revers_sorted_n1 = create_list(number1_elements, reversed_sorted_list)

random_n1 = insertion_with_barrier(random_n1, number1_elements)
sorted_n1 = insertion_with_barrier(sorted_n1, number1_elements)
revers_sorted_n1 = insertion_with_barrier(revers_sorted_n1, number1_elements)

number2_elements = input_errors_checking(
    "\nEnter 2nd number of elements in the list to check time and number of permutations: ", int_type)

while number2_elements < 1:
    print("[!]Error. Number of elements should be bigger then 0. Try again.")
    number2_elements = input_errors_checking(
        "Enter 2nd number of elements in the list to check time and number of permutations: ", int_type)

random_n2 = create_list(number2_elements, random_list)
sorted_n2 = create_list(number2_elements, sorted_list)
revers_sorted_n2 = create_list(number2_elements, reversed_sorted_list)

random_n2 = insertion_with_barrier(random_n2, number2_elements)
sorted_n2 = insertion_with_barrier(sorted_n2, number2_elements)
revers_sorted_n2 = insertion_with_barrier(revers_sorted_n2, number2_elements)

number3_elements = input_errors_checking(
    "\nEnter 3rd number of elements in the list to check time and number of permutations: ", int_type)

while number3_elements < 1:
    print("[!]Error. Number of elements should be bigger then 0. Try again.")
    number3_elements = input_errors_checking(
        "Enter 3rd number of elements in the list to check time and number of permutations: ", int_type)

random_n3 = create_list(number3_elements, random_list)
sorted_n3 = create_list(number3_elements, sorted_list)
revers_sorted_n3 = create_list(number3_elements, reversed_sorted_list)

random_n3 = insertion_with_barrier(random_n3, number3_elements)
sorted_n3 = insertion_with_barrier(sorted_n3, number3_elements)
revers_sorted_n3 = insertion_with_barrier(revers_sorted_n3, number3_elements)

print("\n\n[!]Reminder\nN1 = {:g}\nN2 = {:g}\nN3 = {:g}".format(number1_elements, number2_elements, number3_elements))

print("┌───────────────┬──────────────────────────────┬───────────────────────────────┬──────────────────────────────┐")
print("│               │               N1             │               N2              │              N3              │")
print("├───────────────┼───────────────┬──────────────┼────────────────┬──────────────┼───────────────┬──────────────┤")
print("│               │     time      │ permutations │      time      │ permutations │     time      │ permutations │")
print("├───────────────┼───────────────┼──────────────┼────────────────┼──────────────┼───────────────┼──────────────┤")
print("│     Sorted    │{:15.7g}│{:14.7g}│{:16.7g}│{:14.7g}│{:15.7g}│{:14.7g}│".format(sorted_n1[1], sorted_n1[2],
                                                                                       sorted_n2[1], sorted_n2[2],
                                                                                       sorted_n3[1], sorted_n3[2]))
print("├───────────────┼───────────────┼──────────────┼────────────────┼──────────────┼───────────────┼──────────────┤")
print("│     Random    │{:15.7g}│{:14.7g}│{:16.7g}│{:14.7g}│{:15.7g}│{:14.7g}│".format(random_n1[1], random_n1[2],
                                                                                       random_n2[1], random_n2[2],
                                                                                       random_n3[1], random_n3[2]))
print("├───────────────┼───────────────┼──────────────┼────────────────┼──────────────┼───────────────┼──────────────┤")
print("│ Revers Sorted │{:15.7g}│{:14.7g}│{:16.7g}│{:14.7g}│{:15.7g}│{:14.7g}│".format(revers_sorted_n1[1],
                                                                                       revers_sorted_n1[2],
                                                                                       revers_sorted_n2[1],
                                                                                       revers_sorted_n2[2],
                                                                                       revers_sorted_n3[1],
                                                                                       revers_sorted_n3[2]))
print("└───────────────┴───────────────┴──────────────┴────────────────┴──────────────┴───────────────┴──────────────┘")
