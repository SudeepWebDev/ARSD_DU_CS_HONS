# Defining the find_equation_solutions functions with two parameters num_variable and constant
def find_equation_solutions(num_variable, constant):
    solutions = []

    def solve_equation(variables, remaining):
        if len(variables) == num_variable:
            if remaining == 0:
                solutions.append(variables)
            return

        for i in range(remaining + 1):
            solve_equation(variables + [i], remaining - i)

    solve_equation([], constant)
    return solutions

def main():
    num_variable = int(input("Enter the number of variables: "))
    constant = int(input("Enter the constant (C): "))

    solutions = find_equation_solutions(num_variable, constant)

    print("Solutions:")
    for solution in solutions:
        print(solution)

if __name__ == "__main__":
    main()

