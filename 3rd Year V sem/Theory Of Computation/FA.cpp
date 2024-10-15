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

int main() {
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
    cout << "Enter input string: ";
    cin >> input;

    if (fa.isAccepted(input)) {
        cout << "Accepted" << endl;
    } else {
        cout << "Not Accepted" << endl;
    }

    return 0;
}
