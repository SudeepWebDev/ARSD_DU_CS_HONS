import itertools
import string

def brute_force_attack(target_password, max_length=8):
    characters = string.ascii_letters + string.digits + string.punctuation
    attempts = 0

    for length in range(1, max_length + 1):
        for combination in itertools.product(characters, repeat=length):
            attempts += 1
            guess = ''.join(combination)
            if guess == target_password:
                return guess, attempts

    return None, attempts

if __name__ == "__main__":
    target_password = input("Enter the password to brute force: ")
    max_length = int(input("Enter the maximum length of the password: "))
    found_password, attempts = brute_force_attack(target_password, max_length)
    
    if found_password:
        print(f"Password found: {found_password} in {attempts} attempts.")
    else:
        print(f"Password not found within length {max_length}. Total attempts: {attempts}")
