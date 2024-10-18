import hashlib
import requests

def read_credentials(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    credentials = [line.strip().split(',') for line in lines]
    return credentials

def check_password_leak(password):
    sha1_password = hashlib.sha1(password.encode('utf-8')).hexdigest().upper()
    prefix = sha1_password[:5]
    suffix = sha1_password[5:]
    url = f"https://api.pwnedpasswords.com/range/{prefix}"
    response = requests.get(url)
    hashes = (line.split(':') for line in response.text.splitlines())
    for h, count in hashes:
        if h == suffix:
            return True
    return False

def main(file_path):
    credentials = read_credentials(file_path)
    for username, password in credentials:
        if check_password_leak(password):
            print(f"Password for user {username} has been leaked.")
        else:
            print(f"Password for user {username} is safe.")

if __name__ == "__main__":
    file_path = input("Enter the path to the file containing usernames and passwords: ")
    main(file_path)
