# Kuracheva K. D., ИУ7-13Б
'''
Написать программу для выполнения некоторых операций с текстом. Вводить текст не
требуется, он должен быть задан в исходном тексте программы в виде списка строк
(при выводе на экран каждый элемент этого списка должен начинаться с новой
строки). В качестве текста в программе следует указать фрагмент литературного
произведения из 5-7 предложений, который разбить на 7-10 строк.

Программа должна позволять с помощью меню выполнить следующие действия:
1. Выровнять текст по левому краю.
2. Выровнять текст по правому краю.
3. Выровнять текст по ширине.
4. Удаление всех вхождений заданного слова.
5. Замена одного слова другим во всём тексте.
6. Вычисление арифметических выражений над целыми числами внутри текста
(по варианту).
7. Найти (вывести на экран) и затем удалить слово или предложение по варианту.

Текст следует разбить по строкам так, чтобы предложения не заканчивались в концах
строк (никакая строка, кроме последней, не должна оканчиваться точкой).
'''

from lab12_alignment_left import alignment_left
from lab12_alignment_right import alignment_right
from lab12_alignment_width import alignment_width
from lab12_delete_word import delete_word
from lab12_replace_word import replace_word
from lab12_compute import compute
from lab12_delete_longest_sentence import delete_longest_sentence

given_text = ["Every inch of wall 1 9 space is covered by a bookcase. Each bookcase has -7.67 - 0.67 + 1 shelves, 5.9",
              "-4.9going almost to the ceiling. Some bookshelves are stacked to the brim with hardback books:0-",
              "7science, maths, history, and everything else. Other shelves have two layers",
              "of paperback science fiction, 5+6=11with the back layer of books propped up on old tissue10+",
              "3boxes or lengths of wood, so that you can see the back layer of books above the books in",
              "front. And it still isn't enough. Books are overflowing onto the tables",
              "and the sofas and making little heaps under the win5+5dows."]

menu = ["1. Alignment of the text to the left",
        "2. Alignment of the text to the right",
        "3. Text width alignment",
        "4. Delete all occurrences of a word in the text",
        "5. Replace each occurrences of a word with another word",
        "6. Compute addition and subtraction in the text",
        "7. Find and delete the longest sentence in terms of words",
        "8. Exit the program"]


def input_errors_checking(message):
    parameter = 0
    not_correct_input = 1
    while not_correct_input or parameter < 0 or parameter > 8:
        try:
            parameter = int(input(message))
            if parameter < 0 or parameter > 8:
                raise Exception()
            not_correct_input = 0
        except:
            print("[!]Error. Number of type int should be entered and be bigger then 0 and less then 9. Try again.")

    return parameter


def commands_block():
    command = 0
    while command != 8:
        return_value = 0
        print("\n" + "Menu".center(57) + "\n")
        for line in menu:
            print(line)
        print()
        command = input_errors_checking("Enter command number: ")

        if command == 1:
            return_value = alignment_left(given_text)

        elif command == 2:
            return_value = alignment_right(given_text)

        elif command == 3:
            return_value = alignment_width(given_text)

        elif command == 4:
            word_to_delete = str(input("Enter word to delete: "))
            while word_to_delete == '':
                print("[!]Error. Length of the word should be bigger then 0")
                word_to_delete = str(input("Enter word to delete: "))
            return_value = delete_word(given_text, word_to_delete)

        elif command == 5:
            word_to_replace = str(input("Enter word to replace: "))
            while word_to_replace == '':
                print("[!]Error. Length of the word should be bigger then 0")
                word_to_replace = str(input("Enter word to replace: "))

            word_replacing = str(input("Enter replacing word: "))
            while word_replacing == '':
                print("[!]Error. Length of the word should be bigger then 0")
                word_replacing = str(input("Enter replacing word: "))
            return_value = replace_word(given_text, word_to_replace, word_replacing)

        elif command == 6:
            return_value = compute(given_text)

        elif command == 7:
            return_value = delete_longest_sentence(given_text)

        if command != 8:
            if return_value == 0:
                print("\nEdited text:")
                for line in given_text:
                    print(line)
            else:
                print("\nNothing to edit. Exit the program.")
                command = 8


commands_block()
