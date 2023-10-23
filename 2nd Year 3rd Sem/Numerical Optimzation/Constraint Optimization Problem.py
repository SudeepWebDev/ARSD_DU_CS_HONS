from scipy.optimize import minimize


def objective(x):
    return -2 * x[0] - 2 * x[1] - 3 * x[2]


def constraint1(x):
    return 50 - 2 * x[0] - 7 * x[1] - 3 * x[2]

def constraint2(x):
    return 45 - 3 * x[0] + 5 * x[1] - 7 * x[2]

def constraint3(x):
    return 37 - 5 * x[0] - 2 * x[1] + 6 * x[2]


x0 = [0, 0, 0]
b = (0.0, None)
bnds = (b, b, b)
con1 = {"type": "ineq", "fun": constraint1}
con2 = {"type": "ineq", "fun": constraint2}
con3 = {"type": "ineq", "fun": constraint3}
cons = [con1, con2, con3]
sol = minimize(objective, x0, method="SLSQP", bounds=bnds, constraints=cons)

print(sol)
