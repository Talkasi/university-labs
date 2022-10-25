# Kuracheva K.D., ИУ7-13Б
# Find element with the biggest number of sequenced digits in the list of strings

n = int(input("Enter number of elements in the list: "))
list_n = [""] * n

for i in range(n):
    list_n[i] = str(input("Enter element #{:g}: ".format(i + 1)))

m_digits = 0
m_string = ""
for i in range(n):
    digits_counter = 0
    m_digits_current = 0

    # Searching for the longest sequence of digits in the current string
    for j in range(len(list_n[i])):
        if "0" <= list_n[i][j] <= "9":
            digits_counter += 1
            m_digits_current = digits_counter if digits_counter > m_digits_current else m_digits_current
        else:
            digits_counter = 0

    if m_digits < m_digits_current:
        m_digits = m_digits_current
        m_string = list_n[i]

print(m_string)
