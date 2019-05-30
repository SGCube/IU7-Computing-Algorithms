from physics import atm_to_pascal, pascal_to_atm, eps
from compute import dichotomy

from part1_physics import F_part1


def main():
    p1 = atm_to_pascal(3)
    p2 = atm_to_pascal(25)

    result = dichotomy(p1, p2, eps, 100, F_part1)
    print("Answer: ", pascal_to_atm(result))


if __name__ == '__main__':
    main()
