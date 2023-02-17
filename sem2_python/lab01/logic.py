# Сложение, вычитание и умножение вещественных чисел в 2-й системе счисления.

def equal_form_converter(a, b):
    a = str(a).split(".")
    b = str(b).split(".")

    if len(a) == len(b) == 1:
        return a[0], b[0]

    if len(a) == 1:
        a.append("")
    elif len(a) != 2:
        return -1

    if len(b) == 1:
        b.append("")
    elif len(b) != 2:
        return -1

    a_len_frac = len(a[1])
    b_len_frac = len(b[1])

    if a_len_frac > b_len_frac:
        b[1] += "0" * (a_len_frac - b_len_frac)
    else:
        a[1] += "0" * (b_len_frac - a_len_frac)

    return a[0] + '.' + a[1], b[0] + '.' + b[1]


def delete_zeroes(a):
    z = 0
    for i in range(-1, -len(a) - 1, -1):
        if a[i] == "0":
            z += 1
        else:
            break

    if z != 0:
        a = a[:-z]

    z = 0
    i = 0
    for i in range(len(a)):
        if a[i] == "0":
            z += 1
        else:
            break

    if i + 1 < len(a) and a[i + 1] == '.' and z != 0:
        z -= 1

    if z != 0:
        a = a[z:]

    return a


def sum_(a, b):
    # No signs, equal floating point number of digits

    if len(a) > len(b):
        max_val = a
        min_val = b
    else:
        max_val = b
        min_val = a

    c = ""
    carry = 0
    i = 0
    for i in range(-1, -len(min_val) - 1, -1):
        if a[i] == '.':
            c = "." + c
            continue

        s = int(a[i]) + int(b[i])
        if s != 2:
            if carry + s != 2:
                c = str(carry + s) + c
                carry = 0
            else:
                c = "0" + c
                carry = 1
        else:
            c = str(carry) + c
            carry = 1

    for j in range(i - 1, -len(max_val) - 1, -1):
        if max_val[j] == '.':
            c = "." + c
            continue

        s = int(max_val[j]) + carry
        if s != 2:
            c = str(s) + c
            carry = 0
        else:
            c = "0" + c
            carry = 1

    if carry == 1:
        c = str(carry) + c

    return c


def sub_(a, b):
    # No signs, equal floating point number of digits

    if len(a) > len(b):
        max_val = a
        min_val = b
    else:
        max_val = b
        min_val = a

    c = ""
    carry = 0
    i = 0
    for i in range(-1, -len(min_val) - 1, -1):
        if a[i] == '.':
            c = "." + c
            continue

        s = int(a[i]) - int(b[i])
        if s != -1:
            if carry + s != -1:
                c = str(s + carry) + c
                carry = 0
            else:
                c = "1" + c
                carry = -1
        else:
            if carry == -1:
                c = "0" + c
            else:
                c = "1" + c
            carry = -1

    for j in range(i - 1, -len(max_val) - 1, -1):
        if max_val[j] == '.':
            c = "." + c
            continue

        s = int(max_val[j]) + carry
        if s != -1:
            c = str(s) + c
            carry = 0
        else:
            c = "1" + c
            carry = -1

    if c[0] == "0" and c[1] != ".":
        c = c[1:]

    if c[0] == ".":
        c = "0" + c

    return c


def mul(a, b):
    # No signs, equal floating point number of digits
    a = str(a)
    b = str(b)

    if '.' in a:
        a_point_lpos = len(a) - a.index('.') - 1
        a = a.replace('.', '')
    else:
        a_point_lpos = 0

    if '.' in b:
        b_point_lpos = len(b) - b.index('.') - 1
        b = b.replace('.', '')
    else:
        b_point_lpos = 0

    c_point_lpos = a_point_lpos + b_point_lpos

    if len(a) < len(b):
        a, b = b, a

    c = ""
    ten = ""
    for i in range(-1, -len(b) - 1, -1):
        if int(b[i]):
            current_sum = a
            c = sum_(c, current_sum + ten)
        ten += "0"

    if len(c) and c_point_lpos != 0:
        if len(c) <= c_point_lpos:
            c = "0" * (c_point_lpos - len(c) + 1) + c
        c = c[:-c_point_lpos] + "." + c[-c_point_lpos:]

    return c

