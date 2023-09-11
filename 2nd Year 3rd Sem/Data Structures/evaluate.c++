#include <iostream>
#include <string>
#include <stack>
#include <cmath>
using namespace std;

class EvaluatePostfix
{
private:
    stack<int> Stack;
    bool isOperator(char x)
    {
        switch (x)
        {
        case '$':
        case '+':
        case '-':
        case '/':
        case '*':
            return true;
        }
        return false;
    }

public:
    int calculate(string &postExp)
    {
        for (int i = 0; i < postExp.length(); i++)
        {
            if (isOperator(postExp[i]))
            {
                int b = Stack.top();
                Stack.pop();
                int a = Stack.top();
                Stack.pop();
                if (postExp[i] == '+')
                    Stack.push(a + b);
                else if (postExp[i] == '-')
                    Stack.push(a - b);
                else if (postExp[i] == '*')
                    Stack.push(a * b);
                else if (postExp[i] == '/')
                    Stack.push(a / b);
                else if (postExp[i] == '$')
                    Stack.push(pow(a, b));
            }
            else
            {
                Stack.push(int(postExp[i])-48);
            }
        }
        while (!Stack.empty())
        {
            cout << Stack.top() << " ";
            Stack.pop();
        }

        return Stack.top();
    }
};

int main()
{
    string postExp;
    cout << "Enter postfix expression: " << endl;
    cin >> postExp;
    EvaluatePostfix postfixExpCal;
    cout << "Value of postfix expression: " << postfixExpCal.calculate(postExp) << endl;
    return 0;
}
