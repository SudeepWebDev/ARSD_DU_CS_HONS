# 3. Write a Program that generates all the permutations of a given set of digits, with or without repetition.

# defining the generate_permutations function with two parameters digits and repeat with default value of False.
def generate_permutations(digits, repeat=False):
    result = []
    # calling the function permute with four parametes digits,  empty list, repeat and result
    permute(digits, [], repeat, result)
    return result

# defining the permute function with four parameters.
# digits, current - for current generated permutation, repeat and result - for all generated permuations.
def permute(digits, current, repeat, result):
    if len(current) == len(digits):
        result.append(' '.join(map(str, current)))
    else:
        for digit in digits:
            if not repeat and digit in current:
                continue
            current.append(digit)
            permute(digits, current, repeat, result)
            current.pop()

def main():
    # taking input of the digits
    digits = input("Enter the digits (separated by spaces): ").split()
    repeat = input("Allow repetition? (yes/no): ").lower() == "yes"

    permutations = generate_permutations(digits, repeat)

    print("\nPermutations:")
    for permutation in permutations:
        print(permutation)

if __name__ == "__main__":
    main()
