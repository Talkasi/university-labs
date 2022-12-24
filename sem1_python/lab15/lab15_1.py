# Kuracheva K. D., ИУ7-13Б

# Написать 3 независимые программы для работы с бинарными файлами из целых
# 32-битных чисел, каждая из которых будет реализовывать ввод чисел в файл (если
# файл существует - перезаписывать), соответствующее задание и вывод изменённого
# содержимого файла:
# 1. Удалить все числа, имеющие свойство по варианту, за один проход по файлу.
# 4. Положительные элементы

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

    return 0


def delete_positive_numbers(file):
    file.seek(0, 0)
    s_positive_position = -1
    while True:
        # If the element is negative and start is already saved move element to the start of deleted sequence
        cur_position = file.tell()
        line = file.read(val_size)
        if len(line) == 0:
            break
        cur_number = list(struct.unpack(val_type, line))[0]

        if cur_number <= 0 and s_positive_position != -1:
            position_after_reading = file.tell()

            file.seek(s_positive_position)
            file.write(struct.pack(val_type, cur_number))
            s_positive_position = file.tell()

            file.seek(position_after_reading)
        else:
            # If it is the first positive element in the list save its index as a start index of a sequence
            if cur_number > 0:
                s_positive_position = cur_position if s_positive_position == -1 else s_positive_position

    if s_positive_position != -1:
        file.seek(0, 2)
        file.truncate(s_positive_position)

    return 0


def file_print(file):
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

    write_numbers(file)

    delete_positive_numbers(file)

    file_print(file)

    file.close()


main()
