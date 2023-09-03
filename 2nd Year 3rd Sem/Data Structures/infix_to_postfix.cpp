#include <iostream>
#include <string>
#include <stack>

using namespace std;

class InfixToPostfix
{
private:
	stack<char> opstack;
	string postfixExp;

	int precedence(char op)
	{
		if (op == '+' || op == '-')
			return 1;
		if (op == '*' || op == '/')
			return 2;
		if (op == '$')
			return 3;
		return 0;
	}

public:
	InfixToPostfix()
	{
		postfixExp = "";
	};

	string convert(const string &userExp)
	{
		for (int i = 0; i < userExp.length(); i++)
		{
			char currentChar = userExp[i];

			if (isalnum(currentChar))
			{
				postfixExp += currentChar;
			}
			else if (currentChar == '(')
			{
				opstack.push(currentChar);
			}
			else if (currentChar == ')')
			{
				while (!opstack.empty() && opstack.top() != '(')
				{
					postfixExp += opstack.top();
					opstack.pop();
				}

				if (!opstack.empty())
				{
					opstack.pop();
				}
			}
			else
			{
				while (!opstack.empty() && precedence(opstack.top()) >= precedence(currentChar))
				{
					postfixExp += opstack.top();
					opstack.pop();
				}

				opstack.push(currentChar);
			}
		}
		while (!opstack.empty())
		{
			postfixExp += opstack.top();
			opstack.pop();
		}

		return postfixExp;
	}
};

int main()
{
	string userExp;
	cout << "Enter your infix expression: ";
	cin >> userExp;

	InfixToPostfix converter;
	string postfixExp = converter.convert(userExp);

	cout << "Postfix expression: " << postfixExp << endl;
	return 0;
}
