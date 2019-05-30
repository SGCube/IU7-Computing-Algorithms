
from math import fabs


def middle(a, b):
    return (a + b) / 2


def difference(a, b):
    return fabs(b - a)


def dichotomy(a, b, eps, max_count, func, *args):
    diff = difference(a, b)

    if func(a, *args) > func(b, *args):
        tmp = a
        a = b
        b = tmp

    c = middle(a, b)
    count = 0
    while diff / c > eps and count < max_count:
        if func(c, *args) < 0:
            a = c
        else:
            b = c

        c = middle(a, b)
        diff = difference(a, b)
        count += 1

    return c


def integrate(a, b, func, *args):
    h = 1 / 40
    z = h
    integral_sum = (func(a, *args) * a + func(b, *args) * b) / 2
    while z < 1:
        integral_sum += func(z, *args) * z
        z += h
    integral_sum *= h
    return integral_sum
