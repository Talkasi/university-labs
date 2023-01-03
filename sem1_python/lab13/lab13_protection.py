while True:
    file_name = input("Enter path to a file: ")
    try:
        file = open(file_name, "r")

        file.seek(0, 2)

        if file.tell() == 0:
            print("[!]Error. File is empty.")
        else:
            break
    except:
        print("[!]Error. File can't be opened.")

sentences = []
s = ""
counter = 0

file.seek(0, 0)

for line in file:
    for c in line.strip():
        s += c
        if c == '.':
            sentences.append(s)
            s = ""

        if c == ',':
            counter += 1
    s += " " if len(s) > 0 and s[-1] not in [" ", "."] else ""

file.close()

try:
    file_new = open("{:g}.txt".format(counter), "w")

    for sentence in sentences:
        file_new.write(sentence.strip() + "\n")

    print("[+]Done.")
    file_new.close()
except:
    print("[!]Error. File can't be created.")
