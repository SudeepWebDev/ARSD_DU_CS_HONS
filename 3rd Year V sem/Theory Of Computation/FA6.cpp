#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class FiniteAutomaton
{
public:
    unordered_map<int, unordered_map<char, int>> transitions;
    int initialState;
    unordered_set<int> finalStates;

    FiniteAutomaton() : initialState(-1) {}

    void setInitialState(int state)
    {
        initialState = state;
    }

    void addTransition(int fromState, char input, int toState)
    {
        transitions[fromState][input] = toState;
    }

    void addFinalState(int state)
    {
        finalStates.insert(state);
    }

    bool isAccepted(const string &input) const
    {
        if (initialState == -1)
        {
            cerr << "Initial State not set";
            return false;
        }
        int currentState = initialState;
        for (char c : input)
        {
            auto stateTransitions = transitions.find(currentState);
            if (stateTransitions == transitions.end())
            {
                return false;
            }
            auto nextState = stateTransitions->second.find(c);
            if (nextState == stateTransitions->second.end())
            {
                return false;
            }

            currentState = nextState->second;
        }

        return finalStates.find(currentState) != finalStates.end();
    }
    void printTransitionTable() const
    {
        cout << "Transition Table:" << endl;
        cout << "State" << "\t" << "Input" << "\t" << "Next State" << endl;
        for (const auto &state : transitions)
        {
            for (const auto &trans : state.second)
            {
                cout << state.first << "\t" << trans.first << "\t" << trans.second << endl;
            }
        }
        cout << endl;
    };
};

unordered_set<int> combineSets(const unordered_set<int> &set1, const unordered_set<int> &set2)
{
    unordered_set<int> resultSet = set1;
    resultSet.insert(set2.begin(), set2.end());
    return resultSet;
}

int createStatePair(int state1, int state2, int numStates2)
{
    return state1 * numStates2 + state2;
}

FiniteAutomaton unionFA(const FiniteAutomaton &fa1, const FiniteAutomaton &fa2)
{
    FiniteAutomaton resultFA;
    int numStates2 = fa2.transitions.size();

    resultFA.setInitialState(createStatePair(fa1.initialState, fa2.initialState, numStates2));

    for (const auto &[state1, trans1] : fa1.transitions)
    {
        for (const auto &[state2, trans2] : fa2.transitions)
        {
            for (const auto &[input, nextState1] : trans1)
            {
                int nextState2 = trans2.at(input);
                resultFA.addTransition(createStatePair(state1, state2, numStates2), input, createStatePair(nextState1, nextState2, numStates2));
            }
        }
    }

    for (int finalState1 : fa1.finalStates)
    {
        for (int state2 = 0; state2 < numStates2; ++state2)
        {
            resultFA.addFinalState(createStatePair(finalState1, state2, numStates2));
        }
    }
    for (int finalState2 : fa2.finalStates)
    {
        for (int state1 = 0; state1 < fa1.transitions.size(); ++state1)
        {
            resultFA.addFinalState(createStatePair(state1, finalState2, numStates2));
        }
    }

    return resultFA;
}

FiniteAutomaton intersectionFA(const FiniteAutomaton &fa1, const FiniteAutomaton &fa2)
{
    FiniteAutomaton resultFA;
    int numStates2 = fa2.transitions.size();

    resultFA.setInitialState(createStatePair(fa1.initialState, fa2.initialState, numStates2));

    for (const auto &[state1, trans1] : fa1.transitions)
    {
        for (const auto &[state2, trans2] : fa2.transitions)
        {
            for (const auto &[input, nextState1] : trans1)
            {
                int nextState2 = trans2.at(input);
                resultFA.addTransition(createStatePair(state1, state2, numStates2), input, createStatePair(nextState1, nextState2, numStates2));
            }
        }
    }

    for (int finalState1 : fa1.finalStates)
    {
        for (int finalState2 : fa2.finalStates)
        {
            resultFA.addFinalState(createStatePair(finalState1, finalState2, numStates2));
        }
    }

    return resultFA;
}

FiniteAutomaton concatenateFA(const FiniteAutomaton &fa1, const FiniteAutomaton &fa2)
{
    FiniteAutomaton resultFA;
    int offset = fa1.transitions.size();

    resultFA.transitions = fa1.transitions;
    resultFA.setInitialState(fa1.initialState);
    resultFA.finalStates = fa2.finalStates;

    for (const auto &[state, trans] : fa2.transitions)
    {
        for (const auto &[input, nextState] : trans)
        {
            resultFA.addTransition(state + offset, input, nextState + offset);
        }
    }

    for (int finalState1 : fa1.finalStates)
    {
        resultFA.addTransition(finalState1, 'e', fa2.initialState + offset);
    }

    return resultFA;
}

FiniteAutomaton createFA1()
{
    FiniteAutomaton fa;
    const int q0 = 0, q1 = 1, q2 = 2;

    fa.setInitialState(q0);
    fa.addTransition(q0, 'a', q1);
    fa.addTransition(q1, 'a', q1);
    fa.addTransition(q1, 'b', q1);
    fa.addFinalState(q1);

    return fa;
}

FiniteAutomaton createFA2()
{
    FiniteAutomaton fa;
    const int q0 = 0, q1 = 1;

    fa.setInitialState(q0);
    fa.addTransition(q0, 'a', q0);
    fa.addTransition(q0, 'b', q1);
    fa.addTransition(q1, 'a', q0);
    fa.addTransition(q1, 'b', q1);
    fa.addFinalState(q1);

    return fa;
}
void testFA(const FiniteAutomaton &fa, const vector<string> &testCases)
{
    for (const string &testCase : testCases)
    {
        cout << "Input: " << testCase << " -> " << (fa.isAccepted(testCase) ? "Accepted" : "Rejected") << endl;
    }
}
int main()
{
    FiniteAutomaton fa1 = createFA1();
    FiniteAutomaton fa2 = createFA2();

    FiniteAutomaton unionResult = unionFA(fa1, fa2);
    FiniteAutomaton intersectionResult = intersectionFA(fa1, fa2);
    FiniteAutomaton concatenationResult = concatenateFA(fa1, fa2);
    unionResult.printTransitionTable();
    string input;
    cout << "Enter input string: ";
    cin >> input;

    cout << "Union FA: " << (unionResult.isAccepted(input) ? "Accepted" : "Not Accepted") << endl;
    cout << "Intersection FA: " << (intersectionResult.isAccepted(input) ? "Accepted" : "Not Accepted") << endl;
    cout << "Concatenation FA: " << (concatenationResult.isAccepted(input) ? "Accepted" : "Not Accepted") << endl;
    cout << "Testing Union FA:" << endl;
    vector<string> unionTestCases = {"a", "ab", "b", "ba", "aa", "aab", "bab", "", "bb", "baaa"};
    testFA(unionResult, unionTestCases);

    cout << "\nTesting Intersection FA:" << endl;
    vector<string> intersectionTestCases = {"ab", "aab", "aabb", "", "a", "b", "ba", "aa", "bb", "baaa"};
    testFA(intersectionResult, intersectionTestCases);
    cout << "\nTesting Concatenation FA:" << endl;
    vector<string> concatenationTestCases = {"ab", "aab", "aabb", "aaab", "", "a", "b", "ba", "aa", "bb"};
    testFA(concatenationResult, concatenationTestCases);
    return 0;
}
