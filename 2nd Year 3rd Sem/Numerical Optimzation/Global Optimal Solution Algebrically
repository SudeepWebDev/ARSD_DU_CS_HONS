import numpy as np
from scipy.optimize import minimize_scalar

def f(x):
    return -10 * np.cos(np.pi * x - 2.2) + (x + 1.5) * x

res = minimize_scalar(f, bounds=(-10, 10), method='bounded')
print(f'The global optimal solution of f(x) is {res.x:.4f} with a value of {res.fun:.4f}.')
