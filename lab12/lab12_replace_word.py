

def replace_word(list_of_lines, word_to_replace, word_replacing):
    if len(list_of_lines) == 0:
        print("[!]Error. There is no lines in the list.")
        return -1

    for line_number in range(len(list_of_lines)):
        list_of_lines[line_number] = ' ' + list_of_lines[line_number] + ' '

        for c1 in " @#$%^&*()<>,.:?!'" + '"':
            for c2 in " @#$%^&*()<>,.:?!'" + '"':
                while c1 + word_to_replace + c2 in list_of_lines[line_number]:
                    list_of_lines[line_number] = list_of_lines[line_number].replace(c1 + word_to_replace + c2,
                                                                                    c1 + word_replacing + c2)
        list_of_lines[line_number] = list_of_lines[line_number][1:-1]

    return 0
