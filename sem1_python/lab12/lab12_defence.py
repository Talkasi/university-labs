# предложение, в котором больше всего слов на заданную букву

text = ["This text is a test for this task",
        "and it suppose to be helpful. Also",
        "here is some more sentences. And",
        "more, more, more. Some stuff. Another stuff,",
        "and another stuff, and some more."]


def func():
    char = str(input("> Enter character: "))
    while len(char) != 1:
        print("[!]Error. character is a symbol with length = 1. Try again.")
        char = str(input("> Enter character: "))

    counter = 0
    max_counter = -1
    max_sentence = ""
    s = ""
    for i in range(len(text)):
        s += " " if s != "" else ""
        for j in range(len(text[i])):
            s += text[i][j]
            if text[i][j] == char and (len(s) == 1 or s[-2] == " "):
                counter += 1
            elif text[i][j] == '.':
                if counter > max_counter:
                    max_counter = counter
                    max_sentence = s
                counter = 0
                s = ""

    while max_sentence[0] == " ":
        max_sentence = max_sentence[1:]

    if max_counter == 0:
        print("> There is no words started with the character `{:s}` in the given text.\n"
              "> First sentence of this test is the first line when 0 words you are looking for was found.\n"
              "> Here it is:\n{:s}".format(char, max_sentence))
    else:
        print("> The biggest number of words start with the character `{:s}` is {:g}.\n"
              "> This number of words first was found in this sentence:\n{:s}".format(char, max_counter, max_sentence))


if len(text) == 0:
    print("There is no text to work with")
else:
    func()
