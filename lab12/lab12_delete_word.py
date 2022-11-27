
def delete_word(list_of_lines, word_to_delete):
    for line_number in range(len(list_of_lines)):
        for c in " @#$%^&*()<>,.:?!'" + '"':
            while " " + word_to_delete + c in list_of_lines[line_number]:
                list_of_lines[line_number] = list_of_lines[line_number].replace(" " + word_to_delete + c, c)

    return 0