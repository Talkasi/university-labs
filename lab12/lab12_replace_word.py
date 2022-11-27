

def replace_word(list_of_lines, word_to_replace, word_replacing):
    for line_number in range(len(list_of_lines)):
        for c in " @#$%^&*()<>,.:?!'" + '"':
            while " " + word_to_replace + c in list_of_lines[line_number]:
                list_of_lines[line_number] = list_of_lines[line_number].replace(" " + word_to_replace + c,
                                                                                " " + word_replacing + c)

    return 0
