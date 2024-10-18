def caesar_cipher(text, shift, encrypt=True):
    result = ""
    shift = shift if encrypt else -shift
    for char in text:
        if char.isalpha():
            start = ord('A') if char.isupper() else ord('a')
            result += chr((ord(char) - start + shift) % 26 + start)
        else:
            result += char
    return result

# Taking input from the user
text = input("Enter the text to be encrypted/decrypted: ")
shift = int(input("Enter the shift value: "))
action = input("Type 'encrypt' to encrypt or 'decrypt' to decrypt: ").strip().lower()

# Encrypt or Decrypt based on user input
if action == 'encrypt':
    result = caesar_cipher(text, shift, encrypt=True)
elif action == 'decrypt':
    result = caesar_cipher(text, shift, encrypt=False)
else:
    result = "Invalid action. Please type 'encrypt' or 'decrypt'."

print(f"Result: {result}")
