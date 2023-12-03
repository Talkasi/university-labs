from curses.ascii import isalpha, isdigit

n = int(input("Enter number of elements in the list: "))
list_n = [""] * n

for i in range(n):
    list_n[i] = str(input("Enter element #{:g}: ".format(i + 1)))

m_string = ""
for i in range(n):
    if len(list_n[i]) > 1 and isalpha(list_n[i][0]) and isdigit(list_n[i][1]) or isalpha(list_n[i][1]) \
            and isdigit(list_n[i][0]):

        c, d = 0, 0
        for j in range(len(list_n[i])):
            if not (isalpha(list_n[i][j % 2]) and isalpha(list_n[i][j]) or isdigit(list_n[i][j % 2]) and isdigit(
                    list_n[i][j])):
                break
        else:
            m_string = list_n[i] if len(list_n[i]) > len(m_string) else m_string

if m_string != "":
    print("The longest string consists from sequenced latin characters and digits is {:s}.".format(m_string))
else:
    print("There is no such string in the list")
