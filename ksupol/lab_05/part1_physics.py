
from physics import atm_to_pascal, get_T, K
from compute import integrate


def calc_n_p1(zi, p):
    return K * p / get_T(zi)


def F_part1(p):
    p_start = atm_to_pascal(0.5)
    t_start = 300

    return K * p_start / t_start - 2 * integrate(0, 1, calc_n_p1, p)
