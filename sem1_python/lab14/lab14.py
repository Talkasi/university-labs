# Kuracheva K. D., ИУ7-13Б
'''
Написать программу работы с базой данных в бинарном формате. Предусмотреть выполнение всех приведенных в меню функций.

1. Выбрать файл для работы
2. Инициализировать базу данных (создать либо перезаписать файл и заполнить
его записями)
3. Вывести содержимое базы данных
4. Добавить запись в произвольное место базы данных (пользователь указывает
номер позиции, в которую должна быть вставлена запись)
5. Удалить произвольную запись из базы данных (пользователь указывает номер
удаляемой записи)
6. Поиск по одному полю
7. Поиск по двум полям
'''

import struct

menu = ["1. Choose file to work with",
        "2. Initialize the data_base",
        "3. View the file",
        "4. Add record to the file",
        "5. Delete record in a file",
        "6. Search by parameter in the column",
        "7. Search by parameter in two columns",
        "8. Exit the program"]

table_columns = ["1. Model of the car",
                 "2. License plate",
                 "3. Year of the manufacture",
                 "4. Owners name"]

string_type = "22s12si37s"
string_len = struct.calcsize("22s12si37s")


def database_check(file_name):
    with open(file_name, "rb") as file:
        file.seek(0, 2)
        n_bytes = file.tell()

        if (n_bytes / string_len) == (n_bytes // string_len):
            return 1

    return 0


def initialize(file_name):
    try:
        file = open(file_name, "wb")
    except:
        print("[!]Error. File can't be opened or created. Enter correct file_name.")
        return -1

    if database_check(file_name) == 0:
        print("[!]Error. File is not a database.")
        file.close()
        return -1

    print("\nInitializing the file `{:s}`".format(file_name))

    file.seek(0, 2)
    add_record_file(file_name, file.tell() // string_len + 1)

    while True:
        initializing_state = input("Do you want to add another record to the data_base? [y/n] ")
        if initializing_state in ["Yes", "Y", "yes", "y"]:
            file.seek(0, 2)
            add_record_file(file_name, file.tell() // string_len + 1)

        elif initializing_state in ["No", "N", "no", "n"]:
            break
        else:
            print("[!]Error. Wrong confirming message. Enter any of [`yes`, `y`, `Y`, `Yes`] for yes or "
                  "any of [`no`, `n`, `N`, `No`] for `no`.")

    file.close()
    return 1


def add_record_file(file_name, position=-1):
    try:
        file = open(file_name, "r+b")
    except:
        print("[!]Error. File can't be opened or created. Enter correct file_name.")
        return -1

    if database_check(file_name) == 0:
        print("[!]Error. File is not a database.")
        file.close()
        return -1

    if position == -1:
        file.seek(0, 2)
        position = input_errors_checking("Enter position to add a record on: ", 1, file.tell() // string_len + 1)

    car_model = input("Enter car model: ")
    while len(car_model) > 22:
        print("[!]Error. Length of the model in the record should be less then 23.")
        car_model = input("Enter car model: ")

    license_plate = input("Enter license plate of the car: ")
    while len(license_plate) not in [0, 8, 9]:
        print("[!]Error. Length of the licence plate in the record should be 8 or 9 if the value is defined or 0 if "
              "this parameter is empty.")
        license_plate = input("Enter license plate of the car: ")

    year = input("Enter year of the manufacture: ")
    while len(year) > 4 and len(year) != 0 or (0 < len(year) <= 4 and not (year.isdigit())):
        print("[!]Error. Length of the year of the manufacture in the record should be less then 5 if the value "
              "is defined or 0 if this parameter is empty. \nYear must be an integer.")
        year = input("Enter year of the manufacture: ")

    owners_name = input("Enter owners name: ")
    while len(owners_name) > 37:
        print("[!]Error. Length of the owners name in the record should be bigger then 0 and less then 38.")
        owners_name = input("Enter owners name: ")

    if len(car_model + license_plate + year + owners_name) == 0:
        print("[!]Error. You can't add an empty record to a database, because it doesn't make any sense.")
        file.close()
        return 1

    file.seek(0, 2)
    size = file.tell()
    current_pack = size // string_len

    if size != 0:
        file.seek(size - string_len, 0)

        while current_pack > position - 1:
            previous_pack = file.read(string_len)
            file.write(previous_pack)
            if current_pack - position == 0:
                file.seek(0, 0)
            else:
                file.seek(-string_len * 3, 1)
            current_pack -= 1

        if position != 1:
            file.seek(string_len, 1)

    file.write(struct.pack(string_type, car_model.encode('utf-8'),
                           license_plate.encode('utf-8'), int(year), owners_name.encode('utf-8')))

    file.close()
    return 1


def delete_record_file(file_name):
    try:
        file = open(file_name, "r+b")
    except:
        print("[!]Error. File can't be opened or created. Enter correct file_name.")
        return -1

    if database_check(file_name) == 0:
        print("[!]Error. File is not a database.")
        file.close()
        return -1

    file.seek(0, 2)
    if file.tell() == 0:
        print("File is empty.")
        file.close()
        return 1

    file.seek(0, 2)
    position = input_errors_checking("Enter position of the record to delete: ", 1, file.tell() // string_len)

    file.seek(string_len * position, 0)
    line = 'temp'
    while line:
        line = file.read(string_len)
        file.seek(-string_len * 2, 1)
        file.write(line)
        file.seek(string_len, 1)

    file.seek(0, 2)
    file.truncate(file.tell() - string_len)

    file.close()
    return 1


def view_file(file_name):
    try:
        file = open(file_name, "rb")
    except:
        print("[!]Error. This file can't be opened. Enter correct file_name.")
        return -1

    if database_check(file_name) == 0:
        print("[!]Error. File is not a database.")
        file.close()
        return -1

    file.seek(0, 2)
    if file.tell() == 0:
        print("File is empty.")
        file.close()
        return 1

    print("┌─────────┬────────────────────────┬──────────────┬─────────┬───────────────────────────────────────┐\n"
          "│    #    │       Car model        │   Licence #  │   Year  │              Owners name              │\n"
          "├─────────┼────────────────────────┼──────────────┼─────────┼───────────────────────────────────────┤")

    file.seek(0, 2)
    size = file.tell()
    file.seek(0, 0)

    number = 1
    for pack in range(size // string_len):
        line = file.read(string_len)

        line = list(struct.unpack(string_type, line))

        line[0] = line[0].decode('utf-8')
        line[0] = line[0].replace('\x00', '')

        line[1] = line[1].decode('utf-8')
        line[1] = line[1].replace('\x00', '')

        line[3] = line[3].decode('utf-8')
        line[3] = line[3].replace('\x00', '')

        print("│ {:7g} │ {:22s} │ {:12s} │ {:7g} │ {:37s} │".format(number, line[0], line[1], line[2], line[3]))
        number += 1

    print("└─────────┴────────────────────────┴──────────────┴─────────┴───────────────────────────────────────┘\n")

    file.close()
    return 1


def search_by_1(file_name):
    try:
        file = open(file_name, "rb")
    except:
        print("[!]Error. This file can't be opened. Enter correct file_name.")
        return -1

    if database_check(file_name) == 0:
        print("[!]Error. File is not a database.")
        file.close()
        return -1

    file.seek(0, 2)
    if file.tell() == 0:
        print("File is empty.")
        file.close()
        return 1

    print("\nMenu of columns:")
    for item in table_columns:
        print(item)
    print()

    command = input_errors_checking("Enter number of the column to search by: ", 1, 4)

    parameter = input("Enter item to search by: ")

    file.seek(0, 2)
    size = file.tell()
    file.seek(0, 0)

    found_lines = []
    number = 1
    for pack in range(size // string_len):
        line = file.read(string_len)
        line = list(struct.unpack(string_type, line))

        line[0] = line[0].decode('utf-8')
        line[0] = line[0].replace('\x00', '')

        line[1] = line[1].decode('utf-8')
        line[1] = line[1].replace('\x00', '')

        line[3] = line[3].decode('utf-8')
        line[3] = line[3].replace('\x00', '')

        if str(line[command - 1]) == parameter:
            found_lines.append("│ {:7g} │ {:22s} │ {:12s} │ {:7g} │ {:37s} │".format(number, line[0],
                                                                                     line[1], line[2], line[3]))

        number += 1

    file.close()

    if len(found_lines) > 0:
        print("┌─────────┬────────────────────────┬──────────────┬─────────┬───────────────────────────────────────┐\n"
              "│    #    │       Car model        │   Licence #  │   Year  │              Owners name              │\n"
              "├─────────┼────────────────────────┼──────────────┼─────────┼───────────────────────────────────────┤")

        for line in found_lines:
            print(line)

        print("└─────────┴────────────────────────┴──────────────┴─────────┴───────────────────────────────────────┘\n")

    else:
        print("There are no such lines in the database.")

    return 1


def search_by_2(file_name):
    try:
        file = open(file_name, "rb")
    except:
        print("[!]Error. This file can't be opened. Enter correct file_name.")
        return -1

    if database_check(file_name) == 0:
        print("[!]Error. File is not a database.")
        file.close()
        return -1

    file.seek(0, 2)
    if file.tell() == 0:
        print("File is empty.")
        file.close()
        return 1

    print("\nMenu of columns:")
    for item in table_columns:
        print(item)
    print()

    command_1 = input_errors_checking("Enter number of the column to search by: ", 1, 4)
    parameter1 = input("Enter item to search by: ")

    command_2 = input_errors_checking("\nEnter another number of the column to search by: ", 1, 4)
    while command_2 == command_1:
        print("[!]Error. Numbers of columns should be different.")
        command_2 = input_errors_checking("\nEnter another number of the column to search by: ", 1, 4)

    parameter2 = input("Enter another item to search by: ")

    file.seek(0, 2)
    size = file.tell()
    file.seek(0, 0)

    found_lines = []
    number = 1
    for pack in range(size // string_len):
        line = file.read(string_len)

        line = list(struct.unpack(string_type, line))

        line[0] = line[0].decode('utf-8')
        line[0] = line[0].replace('\x00', '')

        line[1] = line[1].decode('utf-8')
        line[1] = line[1].replace('\x00', '')

        line[3] = line[3].decode('utf-8')
        line[3] = line[3].replace('\x00', '')

        if str(line[command_1 - 1]) == parameter1 and str(line[command_2 - 1]) == parameter2:
            found_lines.append("│ {:7g} │ {:22s} │ {:12s} │ {:7g} │ {:37s} │".format(number, line[0],
                                                                                     line[1], line[2], line[3]))
        number += 1

    file.close()

    if len(found_lines) > 0:
        print("┌─────────┬────────────────────────┬──────────────┬─────────┬───────────────────────────────────────┐\n"
              "│    #    │       Car model        │   Licence #  │   Year  │              Owners name              │\n"
              "├─────────┼────────────────────────┼──────────────┼─────────┼───────────────────────────────────────┤")

        for line in found_lines:
            print(line)

        print("└─────────┴────────────────────────┴──────────────┴─────────┴───────────────────────────────────────┘\n")

    else:
        print("There are no such lines in the database.")

    return 1


def command1():
    file_name = input("Enter path to a file you want to work with: ")
    while len(file_name) < 1:
        print("[!]Error. Length name of file can't be less then 1. Try again.")
        file_name = input("Enter path to a file you want to work with: ")

    return file_name


def input_errors_checking(message, left, right):
    parameter = 0
    not_correct_input = 1
    while not_correct_input:
        try:
            parameter = int(input(message))
            if parameter < left or parameter > right:
                raise Exception()
            not_correct_input = 0
        except:
            print(
                "[!]Error. Number of type int should be entered and be bigger "
                "then {:g} and less then {:g}. Try again.".format(left - 1, right + 1))

    return parameter


def commands_block():
    command = 0
    file_name = ''
    while command != 8:
        print("\nMenu:")
        for item in menu:
            print(item)

        command = input_errors_checking("\nEnter command number: ", 1, 8)

        if command != 1 and command != 8 and file_name == '':
            print("[!]Error. The file to work with should be defined before dealing with it.")
            file_name = command1()

        if command == 1:
            file_name = command1()

        if command == 2:
            if initialize(file_name) == -1:
                file_name = command1()

        elif command == 3:
            if view_file(file_name) == -1:
                print("If you want to work with this file repeat it again to confirm.")
                file_name = command1()

        elif command == 4:
            if add_record_file(file_name) == -1:
                print("If you want to work with this file repeat it again to confirm.")
                file_name = command1()

        elif command == 5:
            if delete_record_file(file_name) == -1:
                print("If you want to work with this file repeat it again to confirm.")
                file_name = command1()

        elif command == 6:
            if search_by_1(file_name) == -1:
                print("If you want to work with this file repeat it again to confirm.")
                file_name = command1()

        elif command == 7:
            if search_by_2(file_name) == -1:
                print("If you want to work with this file repeat it again to confirm.")
                file_name = command1()

        elif command == 8:
            print("Exiting the program.")


commands_block()
