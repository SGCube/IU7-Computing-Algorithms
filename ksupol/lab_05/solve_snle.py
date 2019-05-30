import numpy as np


def gauss(matrix, vector):
    M = np.array(matrix)
    v = np.array(vector)
    v_tmp = np.linalg.solve(M, v)
    return M, v_tmp
