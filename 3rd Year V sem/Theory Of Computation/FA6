#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class FiniteAutomaton {
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

// Helper function to combine two sets
unordered_set<int> combineSets(const unordered_set<int>& set1, const unordered_set<int>& set2) {
    unordered_set<int> resultSet = set1;
    resultSet.insert(set2.begin(), set2.end());
    return resultSet;
}

// Helper function to create a new state for a pair of states from two FAs
int createStatePair(int state1, int state2, int numStates2) {
    return state1 * numStates2 + state2;
}

// Union of two finite automata
FiniteAutomaton unionFA(const FiniteAutomaton& fa1, const FiniteAutomaton& fa2) {
    FiniteAutomaton resultFA;
    int numStates2 = fa2.transitions.size();

    // Set initial state
    resultFA.setInitialState(createStatePair(fa1.initialState, fa2.initialState, numStates2));

    // Combine transitions
    for (const auto& [state1, trans1] : fa1.transitions) {
        for (const auto& [state2, trans2] : fa2.transitions) {
            for (const auto& [input, nextState1] : trans1) {
                int nextState2 = trans2.at(input);
                resultFA.addTransition(createStatePair(state1, state2, numStates2), input, createStatePair(nextState1, nextState2, numStates2));
            }
        }
    }

    // Combine final states
    for (int finalState1 : fa1.finalStates) {
        for (int finalState2 : fa2.finalStates) {
            resultFA.addFinalState(createStatePair(finalState1, finalState2, numStates2));
        }
    }

    return resultFA;
}

// Intersection of two finite automata
FiniteAutomaton intersectionFA(const FiniteAutomaton& fa1, const FiniteAutomaton& fa2) {
    FiniteAutomaton resultFA;
    int numStates2 = fa2.transitions.size();

    // Set initial state
    resultFA.setInitialState(createStatePair(fa1.initialState, fa2.initialState, numStates2));

    // Combine transitions
    for (const auto& [state1, trans1] : fa1.transitions) {
        for (const auto& [state2, trans2] : fa2.transitions) {
            for (const auto& [input, nextState1] : trans1) {
                int nextState2 = trans2.at(input);
                resultFA.addTransition(createStatePair(state1, state2, numStates2), input, createStatePair(nextState1, nextState2, numStates2));
            }
        }
    }

    // Combine final states
    for (int finalState1 : fa1.finalStates) {
        for (int finalState2 : fa2.finalStates) {
            resultFA.addFinalState(createStatePair(finalState1, finalState2, numStates2));
        }
    }

    return resultFA;
}

// Concatenation of two finite automata
FiniteAutomaton concatenateFA(const FiniteAutomaton& fa1, const FiniteAutomaton& fa2) {
    FiniteAutomaton resultFA;
    int offset = fa1.transitions.size();

    // Copy transitions from fa1
    resultFA.transitions = fa1.transitions;
    resultFA.setInitialState(fa1.initialState);
    resultFA.finalStates = fa2.finalStates;

    // Add transitions from fa2 with offset
    for (const auto& [state, trans] : fa2.transitions) {
        for (const auto& [input, nextState] : trans) {
            resultFA.addTransition(state + offset, input, nextState + offset);
        }
    }

    // Add transitions for concatenation
    for (int finalState1 : fa1.finalStates) {
        resultFA.addTransition(finalState1, 'e', fa2.initialState + offset); // 'e' for epsilon transition
    }

    return resultFA;
}

// Example FA1
FiniteAutomaton createFA1() {
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

    return fa;
}

// Example FA2
FiniteAutomaton createFA2() {
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

    return fa;
}

int main() {
    FiniteAutomaton fa1 = createFA1();
    FiniteAutomaton fa2 = createFA2();

    FiniteAutomaton unionResult = unionFA(fa1, fa2);
    FiniteAutomaton intersectionResult = intersectionFA(fa1, fa2);
    FiniteAutomaton concatenationResult = concatenateFA(fa1, fa2);

    string input;
    cout << "Enter input string: ";
    cin >> input;

    cout << "Union FA: " << (unionResult.isAccepted(input) ? "Accepted" : "Not Accepted") << endl;
    cout << "Intersection FA: " << (intersectionResult.isAccepted(input) ? "Accepted" : "Not Accepted") << endl;
    cout << "Concatenation FA: " << (concatenationResult.isAccepted(input) ? "Accepted" : "Not Accepted") << endl;

    return 0;
}
