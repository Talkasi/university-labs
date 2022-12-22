# Kuracheva K. D., ИУ7-13Б

# Написать 3 независимые программы для работы с бинарными файлами из целых
# 32-битных чисел, каждая из которых будет реализовывать ввод чисел в файл (если
# файл существует - перезаписывать), соответствующее задание и вывод изменённого
# содержимого файла:
# После каждого числа, имеющего свойство по варианту, добавить его удвоенное
# значение (допускается два прохода по файлу).
# insertion sort

import struct

val_type = "i"
val_size = struct.calcsize(val_type)


def create_file():
    file_name = input("Enter name of the file to work with: ")
    while len(file_name) < 1:
        print("Error. Length of a file name should be bigger than 0.")
        file_name = input("Enter name of the file to work with: ")

    while True:
        try:
            file = open(file_name, "w+b")
            break
        except:
            print("[!]Error. This file can't be opened.")
            file_name = input("Enter correct name of the file to work with: ")
            while len(file_name) < 1:
                print("Error. Length of a file name should be bigger than 0.")
                file_name = input("Enter name of the file to work with: ")

    return file


def input_error_check(message):
    while True:
        try:
            parameter = int(input(message))

            return parameter
        except:
            print("[!]Error. Value should be an integer.")


def write_numbers(file):
    numbers = input_error_check("Enter number of numbers you want to write into a file: ")
    while numbers <= 0:
        print("[!]Error. Number of numbers you want to write into a file should be bigger than 0.")
        numbers = input_error_check("Enter number of numbers you want to write into a file: ")

    for i in range(numbers):
        cur_number = input_error_check("Enter number #{:g}: ".format(i + 1))
        file.write(struct.pack(val_type, cur_number))

    return numbers


def insertion_sort(numbers, file):
    file.seek(0, 0)

    for i in range(val_size, numbers * val_size, val_size):
        file.seek(i, 0)
        number = list(struct.unpack(val_type, file.read(val_size)))[0]
        tmp = number

        j = i - val_size
        file.seek(j, 0)
        prev = list(struct.unpack(val_type, file.read(val_size)))[0]
        while prev > tmp and j >= 0:
            file.write(struct.pack(val_type, prev))
            j -= val_size
            if j < 0:
                break
            file.seek(j, 0)
            prev = list(struct.unpack(val_type, file.read(val_size)))[0]
        file.seek(j + val_size, 0)
        file.write(struct.pack(val_type, tmp))

    return 0


def file_read(file):
    file.seek(0, 2)
    if file.tell() == 0:
        print("File is empty.")
        return 0

    file.seek(0, 0)
    i = 1
    print("\nNumbers in file:")
    while True:
        line = file.read(val_size)
        if len(line) == 0:
            break
        else:
            cur_number = list(struct.unpack(val_type, line))[0]
            print("Element #{:g}: {:g}".format(i, cur_number))
            i += 1

    return 0


def main():
    file = create_file()

    numbers = write_numbers(file)

    insertion_sort(numbers, file)

    file_read(file)

    file.close()


main()
