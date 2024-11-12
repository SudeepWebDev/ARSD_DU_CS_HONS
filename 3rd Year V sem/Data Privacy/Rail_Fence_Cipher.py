def  encrypt_rail_fence_cipher(text, num_rails):
    if num_rails == 1:
        return text

    rails = ['' for _ in range(num_rails)]
    
    text_length = len(text)
    
    step = 2 * (num_rails - 1)
    
    for rail in range(num_rails):
        index = rail
        while index < text_length:
            rails[rail] += text[index]
            if rail != 0 and rail != num_rails - 1 and (index + step - 2 * rail) < text_length:
                rails[rail] += text[index + step - 2 * rail]
            index += step
    
    ciphered_text = ''.join(rails)
    return ciphered_text


def count_and_divide_text_into_rails(text, num_rails):
    cycle_len = 2 * (num_rails - 1)
    rail_counts = [0] * num_rails
    for i in range(len(text)):
        pos = i % cycle_len
        rail_counts[pos if pos < num_rails else cycle_len - pos] += 1

    rails, idx = [''] * num_rails, 0
    for rail in range(num_rails):
        rails[rail], idx = text[idx:idx + rail_counts[rail]], idx + rail_counts[rail]
    return rails

def decrypt_rail_fence_cipher(cipher, num_rails):
    if num_rails == 1:
        return cipher

    rails = count_and_divide_text_into_rails(cipher, num_rails)
    result, rail_indices, current_rail, step = [], [0] * num_rails, 0, 1

    for _ in range(len(cipher)):
        result.append(rails[current_rail][rail_indices[current_rail]])
        rail_indices[current_rail] += 1
        if current_rail == 0:
            step = 1
        elif current_rail == num_rails - 1:
            step = -1
        current_rail += step
    
    return ''.join(result)


# Example usage
if __name__ == "__main__":
    text = "sudeepkumarsingh"
    num_rails = 3
    ciphered_text = encrypt_rail_fence_cipher(text, num_rails)
    print("Ciphered Text:", ciphered_text)
    decrypted_text = decrypt_rail_fence_cipher(ciphered_text, num_rails)
    print("Decrypted Text:", decrypted_text)
