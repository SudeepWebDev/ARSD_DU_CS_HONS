# Write a Program to evaluate a polynomial function. 
# (For example store f(n)=4n2+2n+ 9 in an array and for a given value of n, say n = 5, 
# compute the value of f(n)).

import numpy as np

# defining the function to evaluate the value of polynomial
def evalPolynomial(degree):
    coeffPolynomial = np.array([])  

    # taking input for each coefficents 
    for i in range(degree + 1):
        coeff = float(input(f'Enter the coefficient of x^{i}: ')) 
        coeffPolynomial = np.append(coeffPolynomial, coeff)  

    print('\nCoefficients:', coeffPolynomial)

    x = float(input('\nEnter the value of the variable for which the value of the polynomial is to be found: '))

    # finding the value of polynomial
    value = 0
    for i in range(degree + 1):
        value += coeffPolynomial[i] * (x ** i)

    print(f'Value of polynomial with coefficients {coeffPolynomial} at {x}: ', value)

def main():
    degree = int(input('Enter the highest degree of your polynomial: '))
    print()
    evalPolynomial(degree)

if __name__ == "__main__":
    main()
