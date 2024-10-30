#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

class TuringMachine {
public:
    void addTransition(int fromState, char input, int toState, char write, char move) {
        transitions[fromState][input] = {toState, write, move};
    }

    string simulate(string input) {
        int currentState = 0;
        int head = 0;
        vector<char> tape(input.begin(), input.end());
        tape.push_back('_'); // End of tape

        while (currentState != -1) {
            char currentChar = tape[head];
            if (transitions[currentState].find(currentChar) == transitions[currentState].end()) {
                return "Not Accepted";
            }

            auto [nextState, writeChar, moveDir] = transitions[currentState][currentChar];
            tape[head] = writeChar;
            currentState = nextState;

            if (moveDir == 'R') {
                head++;
                if (head >= tape.size()) {
                    tape.push_back('_'); // Extend tape with blank if moving right beyond current size
                }
            } else if (moveDir == 'L') {
                head--;
                if (head < 0) {
                    tape.insert(tape.begin(), '_'); // Extend tape on the left with blank if moving left of start
                    head = 0;
                }
            }
        }

        return string(tape.begin(), tape.end());
    }

private:
    map<int, map<char, tuple<int, char, char>>> transitions;
};
void handleAnBnCn() {
    TuringMachine tm;

    // Transition to mark each 'a', 'b', 'c' with 'd' in sequence
    tm.addTransition(0, 'a', 1, 'd', 'R');   // Mark the first 'a' as 'd'
    tm.addTransition(1, 'a', 1, 'a', 'R');   // Move right over remaining 'a's
    tm.addTransition(1, 'd', 1, 'd', 'R');   // Move right over marked 'd's
    tm.addTransition(1, 'b', 2, 'd', 'R');   // Mark the first 'b' as 'd'
    tm.addTransition(2, 'b', 2, 'b', 'R');   // Move right over remaining 'b's
    tm.addTransition(2, 'd', 2, 'd', 'R');   // Move right over marked 'd's
    tm.addTransition(2, 'c', 3, 'd', 'L');   // Mark the first 'c' as 'd' and start moving left

    // Move left to the beginning of the tape to find the next 'a'
    tm.addTransition(3, 'b', 3, 'b', 'L');   // Move left over 'b's
    tm.addTransition(3, 'd', 3, 'd', 'L');   // Move left over 'd's
    tm.addTransition(3, 'a', 3, 'a', 'L');   // Move left over 'a's
    tm.addTransition(3, '_', 0, '_', 'R');   // When blank (start of tape) is reached, go to state 0

    // Final check: Accept if only 'd's and blanks remain
    tm.addTransition(0, 'd', 0, 'd', 'R');   // If all 'a's are marked, proceed to verification
    tm.addTransition(0, '_', -1, '_', 'R');  // Accept if only 'd's and blanks remain

    string input;
    cout << "Enter the string to be tested (a^n b^n c^n): ";
    cin >> input;

    string result = tm.simulate(input);
    if (result == "Not Accepted") {
        cout << "Not Accepted" << endl;
    } else {
        cout << "Accepted" << endl;
    }
}



void handleBinaryIncrement() {
    TuringMachine tm;

    // Define transitions for binary increment
    tm.addTransition(0, '0', 0, '0', 'R');
    tm.addTransition(0, '1', 0, '1', 'R');
    tm.addTransition(0, '_', 1, '_', 'L');
    tm.addTransition(1, '0', -1, '1', 'R');  // End the increment if we find a '0' to flip to '1'
    tm.addTransition(1, '1', 1, '0', 'L');   // Carry over if we find a '1' (flip to '0')
    tm.addTransition(1, '_', -1, '1', 'R');  // If all bits are '1', add '1' at the beginning

    string input;
    cout << "Enter the binary number to increment: ";
    cin >> input;

    string result = tm.simulate(input);
    if (result == "Not Accepted") {
        cout << "Not Accepted" << endl;
    } else {
        // Remove trailing blanks
        auto endPos = find(result.begin(), result.end(), '_');
        result.erase(endPos, result.end());
        cout << "Incremented Result: " << result << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Test a^n b^n c^n" << endl;
        cout << "2. Increment binary number" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                handleAnBnCn();
                break;
            case 2:
                handleBinaryIncrement();
                break;
            case 3:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}

