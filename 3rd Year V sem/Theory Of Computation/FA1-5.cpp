#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class FiniteAutomaton {
private:

public:
    unordered_map<int, unordered_map<char, int>> transitions;
    int initialState;
    unordered_set<int> finalStates;
    FiniteAutomaton() : initialState(-1) {}

    void setInitialState(int state) {
        initialState = state;
    }

    void addTransition(int fromState, char input, int toState) {
        transitions[fromState][input] = toState;
    }

    void addFinalState(int state) {
        finalStates.insert(state);
    }

    bool isAccepted(const string& input) const {
        if (initialState == -1) {
            cerr << "Initial state is not set." << endl;
            return false;
        }

        int currentState = initialState;

        for (char c : input) {
            if (transitions.at(currentState).find(c) == transitions.at(currentState).end()) {
                return false; // Transition not defined for current state and input symbol
            }

            currentState = transitions.at(currentState).at(c);
        }

        return finalStates.find(currentState) != finalStates.end();
    }
};

// FA1: Accepts strings with three consecutive 1's
void runFA1() {
    FiniteAutomaton fa;
    const int q0 = 0, q1 = 1, q2 = 2, q3 = 3;
    
    fa.setInitialState(q0);
    fa.addTransition(q0, '0', q0);
    fa.addTransition(q0, '1', q1);
    fa.addTransition(q1, '0', q0);
    fa.addTransition(q1, '1', q2);
    fa.addTransition(q2, '0', q0);
    fa.addTransition(q2, '1', q3);
    fa.addTransition(q3, '0', q3);
    fa.addTransition(q3, '1', q3);
    fa.addFinalState(q3);

    string input;
    cout << "Enter input string for FA1: ";
    cin >> input;

    if (fa.isAccepted(input)) {
        cout << "Accepted" << endl;
    } else {
        cout << "Not Accepted" << endl;
    }
}

// FA2: Accepts strings with exactly two or three 1's
void runFA2() {
    FiniteAutomaton fa;
    const int q0 = 0, q1 = 1, q2 = 2, q3 = 3, q4 = 4;
    
    fa.setInitialState(q0);
    fa.addTransition(q0, '0', q0);
    fa.addTransition(q0, '1', q1);
    fa.addTransition(q1, '0', q1);
    fa.addTransition(q1, '1', q2);
    fa.addTransition(q2, '0', q2);
    fa.addTransition(q2, '1', q3);
    fa.addTransition(q3, '0', q3);
    fa.addTransition(q3, '1', q4);
    fa.addTransition(q4, '0', q4);
    fa.addTransition(q4, '1', q4);
    fa.addFinalState(q2);
    fa.addFinalState(q3);

    string input;
    cout << "Enter input string for FA2: ";
    cin >> input;

    if (fa.isAccepted(input)) {
        cout << "Accepted" << endl;
    } else {
        cout << "Not Accepted" << endl;
    }
}

// FA3: Accepts strings of length 4 or more with the first two characters the same as the last two
void runFA3() {
    FiniteAutomaton fa;
    const int q0 = 0, q1 = 1, q2 = 2, q3 = 3, q4 = 4, q5 = 5, q6 = 6;

    fa.setInitialState(q0);

    fa.addTransition(q0, 'a', q1);
    fa.addTransition(q0, 'b', q2);
    fa.addTransition(q1, 'a', q3);
    fa.addTransition(q1, 'b', q4);
    fa.addTransition(q2, 'a', q5);
    fa.addTransition(q2, 'b', q6);
    fa.addTransition(q3, 'a', q3);
    fa.addTransition(q3, 'b', q3);
    fa.addTransition(q4, 'a', q4);
    fa.addTransition(q4, 'b', q4);
    fa.addTransition(q5, 'a', q5);
    fa.addTransition(q5, 'b', q5);
    fa.addTransition(q6, 'a', q6);
    fa.addTransition(q6, 'b', q6);
    fa.addFinalState(q3);
    fa.addFinalState(q6);

    string input;
    cout << "Enter input string for FA3: ";
    cin >> input;

    if (fa.isAccepted(input)) {
        cout << "Accepted" << endl;
    } else {
        cout << "Not Accepted" << endl;
    }
}

// FA4: Accepts strings where the language is a(a+b)*b
void runFA4() {
    FiniteAutomaton fa;
    const int q0 = 0, q1 = 1, q2 = 2;

    fa.setInitialState(q0);
    fa.addTransition(q0, 'a', q1);
    fa.addTransition(q1, 'a', q1);
    fa.addTransition(q1, 'b', q2);
    fa.addTransition(q1, 'a', q1);
    fa.addTransition(q2, 'a', q2);
    fa.addTransition(q2, 'b', q2);
    fa.addFinalState(q2);

    string input;
    cout << "Enter input string for FA4: ";
    cin >> input;

    if (fa.isAccepted(input)) {
        cout << "Accepted" << endl;
    } else {
        cout << "Not Accepted" << endl;
    }
}

// FA5: Accepts strings for EVEN-EVEN
void runFA5(){
    FiniteAutomaton fa;

     const int q0 = 0; // even a, even b
    const int q1 = 1; // even a, odd b
    const int q2 = 2; // odd a, even b
    const int q3 = 3; // odd a, odd b

    fa.setInitialState(q0);

    fa.addTransition(q0, 'a', q2);
    fa.addTransition(q0, 'b', q1);
    fa.addTransition(q1, 'a', q3);
    fa.addTransition(q1, 'b', q0);
    fa.addTransition(q2, 'a', q0);
    fa.addTransition(q2, 'b', q3);
    fa.addTransition(q3, 'a', q1);
    fa.addTransition(q3, 'b', q2);

    fa.addFinalState(q0);
     string input;
    cout << "Enter input string for FA5: ";
    cin >> input;

    if (fa.isAccepted(input)) {
        cout << "Accepted" << endl;
    } else {
        cout << "Not Accepted" << endl;
    }
}

int main() {
    int choice;
    cout << "Choose Finite Automaton to run (1-5): ";
    cin >> choice;

    switch (choice) {
        case 1:
            runFA1();
            break;
        case 2:
            runFA2();
            break;
        case 3:
            runFA3();
            break;
        case 4:
            runFA4();
            break;
        case 5:
            runFA5();
            break;
        default:
            cout << "Invalid choice" << endl;
    }

    return 0;
}
