import tkinter
from math import *

import numpy as np
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure


def find_intervals(start, end, step, function):
    x_0 = start
    x_1 = x_0 + step
    intervals = []

    if evaluate(start, function) == 0:
        intervals.append((start, start + step))

    if evaluate(end, function) == 0:
        intervals.append((end - step, end))

    while x_0 < end:
        if evaluate(x_1, function) == 0:
            intervals.append((x_0, x_1))

        elif evaluate(x_0, function) * evaluate(x_1, function) < 0:
            intervals.append((x_0, x_1))

        x_0 += step
        x_1 += step

    return intervals


def clarification(function, start, end, n_max, eps, n):
    n_cur = 0
    x_mid = ""
    interval = "[{:<6.4g}; {:>6.4g}]".format(start, end)
    if evaluate(start, function) == 0:
        return [n + 1, interval, format(start, "<9.4"), format(evaluate(start, function), "<.0e"), n_cur, 0]
    if evaluate(end, function) == 0:
        return [n + 1, interval, format(end, "<9.4"), format(evaluate(end, function), "<.0e"), n_cur, 0]

    while end - start > eps:
        x_mid = start + (end - start) / 2
        if evaluate(start, function) * evaluate(end, function) < 0:
            end = x_mid
        else:
            start = x_mid

        n_cur += 1
        if n_cur >= n_max:
            return [n + 1, interval, "Error", "Error", "Error", 1]

    return [n + 1, interval, format(x_mid, "<9.4"), format(evaluate(x_mid, function), "<.0e"), n_cur, 0]


def evaluate(x, function):
    return eval(function)
