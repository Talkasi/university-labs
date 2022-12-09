from lab12_alignment_left import alignment_left


def alignment_width(list_of_lines):
    if len(list_of_lines) == 0:
        print("[!]Error. There is no lines in the list.")
        return -1

    alignment_left(list_of_lines)

    max_line_len = len(max(list_of_lines, key=len))

    for line_number in range(len(list_of_lines)):
        spaces_number = list_of_lines[line_number].count(' ')
        spaces_place = max_line_len - len(list_of_lines[line_number]) + spaces_number

        current_word_number = 1
        working_line = list_of_lines[line_number].split()[0]
        passed_away = len(list_of_lines[line_number].split()[0])

        while spaces_place > 0 and current_word_number < len(list_of_lines[line_number].split()):
            spaces_place = max_line_len - len(working_line) - (
                    len(list_of_lines[line_number]) - passed_away) + spaces_number

            space_len = round(spaces_place / spaces_number)

            space_current = ' ' * space_len
            spaces_number -= 1

            working_line += space_current + list_of_lines[line_number].split()[current_word_number]
            passed_away += 1 + len(list_of_lines[line_number].split()[current_word_number])
            current_word_number += 1

        list_of_lines[line_number] = working_line

    return 0
