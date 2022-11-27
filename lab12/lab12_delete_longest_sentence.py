
def delete_longest_sentence(list_of_lines):
    index = 0
    max_sentence_len = -1
    max_index = 0
    prev = 0
    for line_number in range(len(list_of_lines)):
        parts_of_sentences = list_of_lines[line_number].split('. ')
        for part_number in range(len(parts_of_sentences)):
            if part_number == 0:
                prev += len(parts_of_sentences[part_number])

                if len(parts_of_sentences) > 1 or (len(parts_of_sentences) == 1 and
                                                   line_number == len(list_of_lines) - 1):
                    index += 1
                    if prev > max_sentence_len:
                        max_sentence_len = prev
                        max_index = index
            elif part_number == len(parts_of_sentences) - 1:
                prev = len(parts_of_sentences[part_number])
            else:
                index += 1
                len_curr = len(parts_of_sentences[part_number])
                if len_curr > max_sentence_len:
                    max_sentence_len = len_curr
                    max_index = index

    index = 0
    print("\nSentence to delete: ")
    for line_number in range(len(list_of_lines)):
        parts_of_sentences = list_of_lines[line_number].split('. ')
        for part_number in range(len(parts_of_sentences)):
            if part_number == 0 and (len(parts_of_sentences) > 1 or (len(parts_of_sentences) == 1
                                                                     and line_number == len(list_of_lines))):
                if max_index - 1 == index:
                    print(parts_of_sentences[part_number] + '. ')
                    list_of_lines[line_number] = \
                            list_of_lines[line_number].replace(parts_of_sentences[part_number] + '. ', '')

                index += 1
            elif part_number == len(parts_of_sentences) - 1:
                if max_index - 1 == index:
                    print(parts_of_sentences[part_number])
                    list_of_lines[line_number] = \
                        list_of_lines[line_number].replace(parts_of_sentences[part_number], '')

            else:
                if max_index - 1 == index:
                    print(parts_of_sentences[part_number] + '. ')
                    list_of_lines[line_number] = \
                        list_of_lines[line_number].replace(parts_of_sentences[part_number] + '. ', '')

                index += 1

    line_number = 0
    while line_number < len(list_of_lines):
        if len(list_of_lines[line_number]) == 0:
            list_of_lines.pop(line_number)
            line_number -= 1

        line_number += 1

    return 0
