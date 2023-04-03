from math import *


def f(x):
    try:
        return eval("cos(x)")
    except:
        return "Error"


def find_iterations(a, b, step):
    intervals = []
    curr = a

    if f(a) == 0:
        intervals.append((a, a + step))

    if f(b) == 0:
        intervals.append((b - step, b))

    while curr < b:
        end = curr + step if curr + step <= b else b
        if f(curr) == "Error" or f(end) == "Error":
            return "Error"

        if f(curr) * f(end) < 0:
            intervals.append((curr, end))

        curr += step

    return intervals


def chords_clarification(a, eps, n_max, n):
    x = a
    x_prev = a + 2 * eps
    n_cur = 0

    while abs(x - x_prev) >= eps:
        x = x - f(x) / (f(x) - f(x_prev)) * (x - x_prev)

        if n_cur >= n_max:
            return [n + 1, (x_prev, x), "Error", "Error", "Error", 1]

        x_prev = x
        n_cur += 1

    return [n + 1, (x_prev, x), x, f(x), n_cur, 1]
