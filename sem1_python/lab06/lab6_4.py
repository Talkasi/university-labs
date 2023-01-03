# Kuracheva K.D., ИУ7-13Б
# Find the longest sequense described in V9
from math import inf

n = int(input("Enter number of elements in the list: "))
list_n = [0] * n

for i in range(n):
    list_n[i] = int(input("Enter element #{:g}: ".format(i + 1)))

list_n.append(-inf)

current_len_sequence = 0
max_len_sequence = 0
start_i = -1
for i in range(n):
    if list_n[i] < 0 and abs(list_n[i]) != 1:
        # Check if the value is prime
        for j in range(2, int(abs(list_n[i]) ** 0.5) + 1):
            if abs(list_n[i]) % j == 0:
                current_len_sequence = 0
                break
        else:
            if (current_len_sequence > 0 and list_n[i - 1] > list_n[i]) or \
                    (current_len_sequence == 0):
                current_len_sequence += 1
                if start_i == -1: start_i = i
                if current_len_sequence > max_len_sequence:
                    max_len_sequence = current_len_sequence
                    searching_start_i = start_i

            elif current_len_sequence > 0 and list_n[i - 1] <= list_n[i]:
                if current_len_sequence > max_len_sequence:
                    max_len_sequence = current_len_sequence
                    searching_start_i = start_i

                current_len_sequence = 1
                start_i = i

            else:
                current_len_sequence = 0
                start_i = -1
    else:
        current_len_sequence = 0
        start_i = -1

if max_len_sequence:
    print("\nThe longest sequence is:")
    for i in range(searching_start_i, searching_start_i + max_len_sequence):
        print("Number in the sequence is {:g},"
              " element is {:g}".format(i + 1, list_n[i]))
else:
    print("\nThere is no such sequence in this list.")
