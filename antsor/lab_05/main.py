"""

Лабораторная работа №5
Курс: Вычислительные алгоритмы
Тема: Решение систем нелинейных уравнений

Модуль: Основной

Copyright Сорокин Антон, гр. ИУ7-42Б

"""

from physics import atm_to_pascal, pascal_to_atm, F, eps
from simplemath import dichotomy


def main():
    p1 = atm_to_pascal(3)
    p2 = atm_to_pascal(25)

    result = dichotomy(p1, p2, eps, 100, F)
    print("Answer: ", pascal_to_atm(result))


if __name__ == '__main__':
    main()
