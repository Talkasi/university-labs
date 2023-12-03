def ten_four(a):
    max_four = 1
    n_four = 0
    while a >= max_four:
        max_four *= 4
        n_four += 1

    # print(max_four, n_four)
    max_four //= 4
    n_four -= 1

    # print(max_four, n_four)
    c = 0

    while n_four > -1:
        # print(c, n_four)
        c += a // pow(4, n_four) * pow(10, n_four)
        a = a % pow(4, n_four)
        n_four -= 1

    return c


def four_ten(a):
    n = 1
    c = 0
    while a > 0:
        c += a % 10 * pow(4, n - 1)
        a //= 10
        n += 1
        # print(c, a, n)

    return c


# print(ten_four(20))
print(four_ten(400000))
