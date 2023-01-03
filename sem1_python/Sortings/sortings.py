def quick_sort(numbers):
    if len(numbers) > 1:
        chosen_element = numbers[(len(numbers) - 1) // 2]
        less = []
        equal = []
        greater = []
        for element in numbers:
            if element < chosen_element:
                less.append(element)
            elif element == chosen_element:
                equal.append(element)
            else:
                greater.append(element)

        numbers = quick_sort(less) + equal + quick_sort(greater)

    return numbers


def insertions(numbers):
    for i in range(len(numbers) - 1):
        tmp = numbers[i + 1]
        j = i

        while j >= 0 and numbers[j] > tmp:
            numbers[j + 1] = numbers[j]
            j -= 1

        numbers[j + 1] = tmp

    return numbers


def insertions_with_barrier(numbers):
    numbers = [0.0] + numbers

    for i in range(1, len(numbers) - 1):
        numbers[0] = numbers[i + 1]
        j = i

        while numbers[0] < numbers[j]:
            numbers[j + 1] = numbers[j]
            j -= 1

        numbers[j + 1] = numbers[0]

    numbers.pop(0)
    return numbers


def binary_insertions(numbers):
    for i in range(len(numbers) - 1):
        if numbers[i] > numbers[i + 1]:
            tmp = numbers[i + 1]

            left = 0
            right = i
            while right - left > 0:
                mid = left + (right - left) // 2
                if numbers[mid] > tmp:
                    right = mid
                else:
                    left = mid + 1

            for j in range(i + 1, left, -1):
                numbers[j] = numbers[j - 1]

            numbers[left] = tmp

    return numbers


def gnome_sorting(numbers):
    i = 1
    j = 2
    while i < len(numbers):
        if numbers[i - 1] < numbers[i]:
            i = j
            j = j + 1
        else:
            numbers[i - 1],  numbers[i] = numbers[i], numbers[i - 1]
            i = i - 1
            if i == 0:
                i = j
                j = j + 1
    return numbers


list_numbers = [90, -9, 9, 4, 6, -100, -3]
print("Given list:               ", *list_numbers, "\n")

print("Quick sort:               ", *quick_sort([90, -9, 9, 4, 6, -100, -3]))
print("Insertions:               ", *insertions([90, -9, 9, 4, 6, -100, -3]))
print("Insertions with barrier:  ", *insertions_with_barrier([90, -9, 9, 4, 6, -100, -3]))
print("Binary insertions:        ", *binary_insertions([90, -9, 9, 4, 6, -100, -3]))
print("Gnome sorting:            ", *gnome_sorting([90, -9, 9, 4, 6, -100, -3]))
