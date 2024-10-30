#include <iostream>
#include <stack>
#include <string>

using namespace std;

class PDA {
public:
    // Simulate PDA for {a^n b^n | n > 0}
    bool simulateAnBn(const string &input) {
        stack<char> st;
        int i = 0;

        // Push 'a's onto the stack
        while (i < input.length() && input[i] == 'a') {
            st.push('a');
            i++;
        }

        // Pop 'a's for each 'b' encountered
        while (i < input.length() && input[i] == 'b') {
            if (st.empty() || st.top() != 'a') return false;
            st.pop();
            i++;
        }

        // The input is valid if the stack is empty and all characters are processed
        return st.empty() && i == input.length();
    }

    // Simulate PDA for {w X w^r | w ∈ {a, b}*, X is a special symbol}
    bool simulateWXRWr(const string &input) {
        stack<char> st;
        int i = 0;

        // Push 'a' or 'b' onto the stack until 'X' is found
        while (i < input.length() && input[i] != 'X') {
            st.push(input[i]);
            i++;
        }

        // Check for presence of 'X'
        if (i == input.length() || input[i] != 'X') return false;
        i++;  // Move past 'X'

        // For each character after 'X', pop from the stack and check if it matches
        while (i < input.length()) {
            if (st.empty() || st.top() != input[i]) return false;
            st.pop();
            i++;
        }

        // The input is valid if the stack is empty and all characters are processed
        return st.empty();
    }

    // Menu to select and simulate each PDA
    void run() {
        int choice;
        string input;

        do {
            cout << "\nMenu:\n";
            cout << "1. Test language {a^n b^n | n > 0}\n";
            cout << "2. Test language {w X w^r | w ∈ {a, b}*}\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter the string to test (a^n b^n): ";
                    cin >> input;
                    if (simulateAnBn(input)) {
                        cout << "Accepted\n";
                    } else {
                        cout << "Not Accepted\n";
                    }
                    break;
                case 2:
                    cout << "Enter the string to test (w X w^r): ";
                    cin >> input;
                    if (simulateWXRWr(input)) {
                        cout << "Accepted\n";
                    } else {
                        cout << "Not Accepted\n";
                    }
                    break;
                case 3:
                    cout << "Exiting the program.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 3);
    }
};

int main() {
    PDA pda;
    pda.run();
    return 0;
}
