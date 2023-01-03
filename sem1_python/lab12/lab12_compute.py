def compute(list_of_lines):
    if len(list_of_lines) == 0:
        print("[!]Error. There is no lines in the list.")
        return -1

    index_start_computing = 0
    computing_flag = 0
    current_number = ''
    result = 0
    new_line_flag = 0
    for line_number in range(len(list_of_lines)):
        if current_number != '':
            result = computing_flag * float(current_number) if computing_flag != 0 else float(current_number)
            new_line_flag = 1
            current_number = ''

        i = 0
        while i < len(list_of_lines[line_number]):
            # If current char is part of a number: digit or a point
            if list_of_lines[line_number][i].isdigit() or (list_of_lines[line_number][i] == '.'
                                                           and current_number != ''):
                # Store start of the number if new computing started
                if current_number == '' and computing_flag == 0:
                    index_start_computing = i
                # Collect parts of the number
                current_number += list_of_lines[line_number][i]

            # If computing type is being defined
            elif list_of_lines[line_number][i] == "+" or list_of_lines[line_number][i] == "-":
                # If we already have the number
                if current_number != '':
                    result += computing_flag * float(current_number) if computing_flag != 0 else float(current_number)

                index_start_computing = i if new_line_flag == 0 and current_number == '' else index_start_computing
                current_number = ''
                computing_flag = 1 if list_of_lines[line_number][i] == "+" else -1

            # If another symbol (ignoring spaces)
            elif list_of_lines[line_number][i] != " ":

                if computing_flag != 0:
                    # If we have another number, compute
                    if current_number != '':
                        result += computing_flag * float(current_number)

                    # Store an answer
                    if index_start_computing < i:
                        list_of_lines[line_number] = \
                            list_of_lines[line_number][:index_start_computing] + "{:.5g}".format(result) + \
                            list_of_lines[line_number][i - 1 if list_of_lines[line_number][i - 1] == ' ' else i:]

                        i -= (i - index_start_computing) - len(str(result))
                    else:
                        list_of_lines[line_number - 1] = list_of_lines[line_number - 1][:index_start_computing] + \
                                                         "{:.5g}".format(result)
                        list_of_lines[line_number] = list_of_lines[line_number][i:]
                        i = 0
                new_line_flag = 0
                current_number = ''
                computing_flag = 0
                result = 0
            i += 1

    return 0
