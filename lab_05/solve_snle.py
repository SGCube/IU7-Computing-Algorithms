"""

Лабораторная работа №5
Курс: Вычислительные алгоритмы
Тема: Решение систем нелинейных уравнений

Модуль: Решение системы

Copyright Сорокин Антон, гр. ИУ7-42Б

"""

import numpy as np


def gauss(matrix, vector):
    M = np.array(matrix)
    v = np.array(vector)
    v_tmp = np.linalg.solve(M, v)
    return M, v_tmp
