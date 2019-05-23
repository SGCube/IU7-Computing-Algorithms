"""

Лабораторная работа №5
Курс: Вычислительные алгоритмы
Тема: Решение систем нелинейных уравнений

Модуль: Физические методы и константы

Copyright Сорокин Антон, гр. ИУ7-42Б

"""

from math import exp, log, fabs
from simplemath import integrate, dichotomy
from interp import interpolate
from solve_snle import gauss

# constants
K = 7242
m = 8
T0 = 5000
Tw = 2000

E = [12.13, 20.98, 31.00, 45.00]

x_start = [3, -1, -10, -20, -35]
v_start = -1

eps = 1e-4


def atm_to_pascal(a):
    return a * 101325


def pascal_to_atm(p):
    return p / 101325


def ev_to_joule(ev):
    return ev * 1.6 * 1e-19


def get_T(zi):
    return T0 + (Tw - T0) * pow(zi, m)


def get_Q(T):
    Q = interpolate("static_sum.txt", T, 5)
    return Q


def get_dE(T, z, G):
    dE = []
    for i in range(0, 4):
        num = 8.61 * 1e-5 * T * log((1 + pow(z[i + 1], 2) * (G / 2)) * (1 + G / 2) /
                                           (1 + pow(z[i + 1], 2) * (G / 2)))
        dE.append(num)
    return dE


def get_K(T, z, G, E, dE, Q):
    K = []
    for i in range(0, 4):
        num = 2 * 2.415 * 1e-3 * Q[i + 1] / Q[i] * pow(T, 1.5) * exp(-(E[i] - dE[i]) * (11603 / T))
        K.append(num)
    return K


def get_f(G, T, V, X, z):
    num_sum = 0

    for i in range(1, 5):
        num_sum += exp(X[i] * pow(z[i], 2) / (1 + pow(z[i], 2) * (G / 2)))

    y = pow(G, 2) - 5.87 * 1e+10 * (1 / pow(T, 3)) * (exp(V) / (1 + G / 2) + num_sum)
    return y


def get_matrix(T, p, G, X, K, V, z):
    n = len(X) + 1
    matrix = [[0 for i in range(n)] for j in range(n)]
    vector = [0] * n

    for i in range(n - 2):
        matrix[i][0] = 1
        matrix[i][i + 1] = -1
        matrix[i][i + 2] = 1

    matrix[n - 2][0] = exp(V)
    matrix[n - 1][0] = -exp(V)

    for i in range(1, n):
        matrix[n - 2][i] = -z[i - 1] * exp(X[i - 1])
        matrix[n - 1][i] = -exp(X[i - 1])

    for i in range(n - 2):
        num = -(V + X[i + 1] - X[i] - log(K[i]))
        vector[i] = num

    num = exp(V)
    for i in range(1, n - 1):
        num -= z[i] * exp(X[i])
    vector[n - 2] = -num

    num = 0.285 * 1e-11 * pow(G * T, 3) + p * 7242 / T - exp(V)
    for i in range(0, 5):
        num -= exp(X[i])
    vector[n - 1] = -num

    return matrix, vector


def calc_n(zi, p):
    p = pascal_to_atm(p)
    X = x_start.copy()
    V = v_start
    T = get_T(zi)
    Q = get_Q(T)

    err = [0, 0, 0, 0, 0, 0]
    dx = [3, -1, -10, -20, -35]
    z = [0, 1, 2, 3, 4]

    while True:
        G = dichotomy(0, 3, eps, 10, get_f, T, V, X, z)
        dE = get_dE(T, z, G)
        K = get_K(T, z, G, E, dE, Q)
        matrix, vector = get_matrix(T, p, G, X, K, V, z)
        matrix, vector = gauss(matrix, vector)

        dv = vector[0]
        err[0] = vector[0] / V
        V += dv

        for i in range(0, 5):
            dx[i] = vector[i + 1]
            err[i + 1] = fabs(vector[i + 1] / X[i])
            X[i] += dx[i]

        if max(err) < eps:
            break

    num_sum = 0
    for x in X:
        num_sum += exp(x)

    return atm_to_pascal(num_sum)


def F(p):
    p_start = atm_to_pascal(0.5)
    t_start = 300

    return K * p_start / t_start - 2 * integrate(0, 1, calc_n, p)
