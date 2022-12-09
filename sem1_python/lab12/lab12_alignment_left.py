
# Aligns text to the left
def alignment_left(list_of_lines):
    if len(list_of_lines) == 0:
        print("[!]Error. There is no lines in the list.")
        return -1

    for line_number in range(len(list_of_lines)):
        list_of_lines[line_number] = ' '.join(i for i in list_of_lines[line_number].split() if i != '')

    return 0
