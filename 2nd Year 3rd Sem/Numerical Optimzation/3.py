import numpy as np


def gradient(x):
    return np.array(
        [400 * x[0] * (x[0] ** 2 - x[1]) - 2 * (1 - x[0]), 200 * (x[1] - x[0] ** 2)]
    )


def hessian(x):
    return np.array(
        [[1200 * x[0] ** 2 - 400 * x[1] + 2, -400 * x[0]], [-400 * x[0], 200]]
    )


# Test the functions
x = np.array([1, 1])
print("Gradient at x = {}: {}".format(x, gradient(x)))
print("Hessian at x = {}: {}".format(x, hessian(x)))
