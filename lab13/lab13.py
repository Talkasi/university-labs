menu = ["1. Choose file to work with",
        "2. Initialize the data_base",
        "3. View the file",
        "4. Add record to the end of file",
        "5. Search by parameter in the column",
        "6. Search by parameter in two columns",
        "7. Exit the program"]

table_columns = ["1. Model of the car",
                 "2. License plate",
                 "3. Year of the manufacture",
                 "4. Owners name"]


def data_base_check(file_name):
    with open(file_name, "r") as file:
        for line in file:
            if line.count(',') != 4:
                print("[!]Error. File is not a data_base.")
                return 0

            line_split = line.split(',')
            if len(line_split[0]) > 22 or (len(line_split[2]) != 4 and len(line_split[2]) != 0) or \
                    (len(line_split[1]) > 9 or (len(line_split[1]) < 8 and len(line_split[1]) != 0)) or \
                    len(line_split[3]) > 43:
                print("[!]Error. File is not a data_base.")
                return 0

    return 1


def initialize(file_name):
    try:
        file = open(file_name, "w")
    except:
        print("[!]Error. File can't be opened or created. Enter correct file_name.")
        return -1

    print("\nInitializing the file `{:s}`".format(file_name))
    add_record_file(file_name)

    while True:
        initializing_state = input("Do you want to add another record to the data_base? [y/n] ")
        if initializing_state in ["Yes", "Y", "yes", "y"]:
            add_record_file(file_name)

        elif initializing_state in ["No", "N", "no", "n"]:
            break
        else:
            print("[!]Error. Wrong confirming message. Enter any of [`yes`, `y`, `Y`, `Yes`] for yes or "
                  "any of [`no`, `n`, `N`, `No`] for `no`.")

    file.close()
    return 1


def view_file(file_name):
    try:
        file = open(file_name, "r")
    except:
        print("[!]Error. This file can't be opened. Enter correct file_name.")
        return -1

    if data_base_check(file_name) != 1:
        return 0

    for line in file:
        break
    else:
        print("File is empty.")
        return 1

    file.seek(0, 0)

    print("┌────────────────────────┬──────────────┬─────────┬─────────────────────────────────────────────┐\n"
          "│       Car model        │   Licence #  │   Year  │                 Owners name                 │\n"
          "├────────────────────────┼──────────────┼─────────┼─────────────────────────────────────────────┤")

    for line in file:
        line_split = line.split(',')
        print("│ {:22s} │ {:12s} │ {:7s} │ {:43s} │".format(line_split[0], line_split[1], line_split[2], line_split[3]))

    print("└────────────────────────┴──────────────┴─────────┴─────────────────────────────────────────────┘\n")

    file.close()
    return 1


def add_record_file(file_name):
    try:
        file = open(file_name, "a")
    except:
        print("[!]Error. File can't be opened or created. Enter correct file_name.")
        return -1

    if data_base_check(file_name) != 1:
        return 0

    car_model = input("Enter car model: ")
    while len(car_model) > 22 or ',' in car_model:
        print("[!]Error. Length of the model in the record should be less then 23."
              "\n There must be no `,` in the record.")
        car_model = input("Enter car model: ")

    license_plate = input("Enter license plate of the car: ")
    while (len(license_plate) > 9 or (len(license_plate) < 8 and len(license_plate) != 0)) or ',' in license_plate:
        print("[!]Error. Length of the licence plate in the record should be 8 or 9 if the value is defined or 0 if "
              "this parameter is empty.\n There must be no `,` in the record.")
        license_plate = input("Enter license plate of the car: ")

    year = input("Enter year of the manufacture: ")
    while (len(year) != 4 and len(year) != 0) or ',' in year:
        print("[!]Error. Length of the year of the manufacture in the record should be 4 if the value is defined or 0 "
              "if this parameter is empty.\n There must be no `,` in the record.")
        year = input("Enter year of the manufacture: ")

    owners_name = input("Enter owners name: ")
    while len(owners_name) > 43 or ',' in owners_name:
        print("[!]Error. Length of the owners name in the record should be bigger then 0 and less then 44."
              "\n There must be no `,` in the record.")
        owners_name = input("Enter owners name: ")

    if len(car_model + license_plate + year + owners_name) == 0:
        while True:
            adding_state = input("You are trying to add an empty record to a data_base. Are you sure? [y/n] ")
            if adding_state in ["Yes", "Y", "yes", "y"]:
                line = "{:s},{:s},{:s},{:s},\n".format(car_model, license_plate, year, owners_name)
                file.write(line)
                break
            elif adding_state in ["No", "N", "no", "n"]:
                break
            else:
                print("[!]Error. Wrong confirming message. Enter any of [`yes`, `y`, `Y`, `Yes`] for yes or "
                      "any of [`no`, `n`, `N`, `No`] for `no`.")

    file.close()
    return 1


def search_by_1(file_name):
    try:
        file = open(file_name, "r")
    except:
        print("[!]Error. This file can't be opened. Enter correct file_name.")
        return -1

    if data_base_check(file_name) != 1:
        return 0

    for line in file:
        break
    else:
        print("File is empty.")
        return 1

    file.seek(0, 0)
    print("\nMenu of columns:")
    for item in table_columns:
        print(item)

    command = input_errors_checking("Enter number of the column to search by: ", 1, 4)

    parameter = input("Enter item to search by: ")

    found_lines = []
    for line in file:
        line_split = line.split(',')
        if line_split[command - 1] == parameter:
            found_lines.append("│ {:22s} │ {:12s} │ {:7s} │ {:43s} │".format(line_split[0], line_split[1],
                                                                             line_split[2], line_split[3]))
    file.close()

    if len(found_lines) > 0:
        print("┌────────────────────────┬──────────────┬─────────┬─────────────────────────────────────────────┐\n"
              "│       Car model        │   Licence #  │   Year  │                 Owners name                 │\n"
              "├────────────────────────┼──────────────┼─────────┼─────────────────────────────────────────────┤")

        for line in found_lines:
            print(line)

        print("└────────────────────────┴──────────────┴─────────┴─────────────────────────────────────────────┘\n")

    else:
        print("There are no such lines in the data_base.")

    return 1


def search_by_2(file_name):
    try:
        file = open(file_name, "r")
    except:
        print("[!]Error. This file can't be opened. Enter correct file_name.")
        return -1

    if data_base_check(file_name) != 1:
        return 0

    for line in file:
        break
    else:
        print("File is empty.")
        return 1

    file.seek(0, 0)

    print("\nMenu of columns:")
    for item in table_columns:
        print(item)

    command_1 = input_errors_checking("Enter number of the column to search by: ", 1, 4)
    parameter1 = input("Enter item to search by: ")

    command_2 = input_errors_checking("\nEnter another number of the column to search by: ", 1, 4)
    while command_2 == command_1:
        print("[!]Error. Numbers of columns should be different.")
        command_2 = input_errors_checking("\nEnter another number of the column to search by: ", 1, 4)

    parameter2 = input("Enter another item to search by: ")

    found_lines = []
    for line in file:
        line_split = line.split(',')
        if line_split[command_1 - 1] == parameter1 and line_split[command_2 - 1] == parameter2:
            found_lines.append("│ {:22s} │ {:12s} │ {:7s} │ {:43s} │".format(line_split[0], line_split[1],
                                                                             line_split[2], line_split[3]))
    file.close()

    if len(found_lines) > 0:
        print("┌────────────────────────┬──────────────┬─────────┬─────────────────────────────────────────────┐\n"
              "│       Car model        │   Licence #  │   Year  │                 Owners name                 │\n"
              "├────────────────────────┼──────────────┼─────────┼─────────────────────────────────────────────┤")

        for line in found_lines:
            print(line)

        print("└────────────────────────┴──────────────┴─────────┴─────────────────────────────────────────────┘\n")

    else:
        print("There are no such lines in the data_base.")

    return 1


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


def command1():
    file_name = input("Enter path to a file you want to work with: ")
    while len(file_name) < 1:
        print("[!]Error. Length name of file can't be less then 1. Try again.")
        file_name = input("Enter path to a file you want to work with: ")

    return file_name


def commands_block():
    command = 0
    file_name = ''
    while command != 7:
        print("\nMenu:")
        for item in menu:
            print(item)

        command = input_errors_checking("\nEnter command number: ", 1, 8)

        if command != 1 and command != 7 and file_name == '':
            print("[!]Error. The file to work with should be defined before dealing with it.")
            file_name = command1()

        if command == 1:
            file_name = command1()

        if command == 2:
            if initialize(file_name) == -1:
                file_name = command1()

        elif command == 3:
            if view_file(file_name) == -1:
                file_name = command1()

        elif command == 4:
            if add_record_file(file_name) == -1:
                file_name = command1()

        elif command == 5:
            if search_by_1(file_name) == -1:
                file_name = command1()

        elif command == 6:
            if search_by_2(file_name) == -1:
                file_name = command1()

        elif command == 7:
            print("Exiting the program.")


commands_block()
