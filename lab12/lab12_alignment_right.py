from lab12_alignment_left import alignment_left


def alignment_right(list_of_lines):
    alignment_left(list_of_lines)

    max_line = max(list_of_lines, key=len)

    for line_number in range(len(list_of_lines)):
        list_of_lines[line_number] = list_of_lines[line_number].rjust(len(max_line))

    return 0
