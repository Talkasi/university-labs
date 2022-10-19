# Kuracheva K.D., ИУ7-13Б

n = int(input("Enter number of elements in the list: "))
list_n = [0] * n

for i in range(n):
    list_n[i] = int(input("Enter element #{:g}: ".format(i + 1)))

current_sequence = []
max_sequence = []
for i in range(n):
    if ((len(current_sequence) > 0 and current_sequence[-1] > list_n[i]) or
        (len(current_sequence) == 0 and list_n[i] < 0)) and abs(list_n[i]) != 1:
        for j in range(2, int(abs(list_n[i]) ** 0.5) + 1):
            if abs(list_n[i]) % j == 0:
                current_sequence = []
                break
        else:
            current_sequence.append(list_n[i])
    else:
        current_sequence = []

    max_sequence = current_sequence if len(current_sequence) > len(max_sequence) else max_sequence

if max_sequence:
    print("\nThe longest sequence is:")
    for i in range(len(max_sequence)):
        print("Number in the sequence is {:g}, element is {:g}".format(i + 1, max_sequence[i]))
else:
    print("\nThere is no such sequence in this list.")
