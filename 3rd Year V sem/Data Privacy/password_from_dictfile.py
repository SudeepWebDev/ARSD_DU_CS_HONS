import random

def generate_password(num_words=4, dictionary_file="dict.txt"):
    try:
        with open(dictionary_file, "r") as file:
            words = file.read().splitlines()
        
        if not words:
            raise ValueError("Dictionary file is empty.")
        
        selected_words = random.sample(words, num_words)
        
        password = ''.join(selected_words)
        
        return password
    except FileNotFoundError:
        return "Dictionary file not found. Please check the file path."
    except ValueError as ve:
        return f"Error: {ve}"

if __name__ == "__main__":
    num_words = 4  # Number of words to combine for the password
    print("Generated Password:", generate_password(num_words))
