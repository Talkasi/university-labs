from math import *


def clarification(func, a, b):
    try:
        eps = 1e-8
        while abs(a - b) >= eps:
            a = a - (b - a) * f(a, func) / (f(b, func) - f(a, func))
            b = b - (a - b) * f(b, func) / (f(a, func) - f(b, func))

        return a
    except:
        return "Error in evaluating"


def f(x, func):
    try:
        return eval(func)
    except:
        return "Error"

