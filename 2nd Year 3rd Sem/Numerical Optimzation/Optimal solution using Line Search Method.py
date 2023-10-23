import numpy as np
from scipy.optimize import minimize_scalar


def objective_function(x):
    return (x - 0.5) ** 2


def line_search_optimization():
    # define the starting point
    x0 = 1.0
    # perform the line search optimization
    result = minimize_scalar(objective_function, method="brent")
    # summarize the result
    print("Status : %s" % result["message"])
    print("Total Evaluations: %d" % result["nfev"])
    print("Optimal Solution: x=%.3f" % result["x"])
    print("Objective Function Value: f(x)=%.3f" % result["fun"])


line_search_optimization()
