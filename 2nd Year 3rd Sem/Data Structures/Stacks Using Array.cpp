#include <iostream>
using namespace std;

class Stack
{
private:
    int top;
    int stackArr[8];
    int size = 8;

public:
    Stack();
    bool isEmpty();
    bool isFull();
    void push();
    void pop();
    void display();
};

Stack::Stack()
{
    top = -1;
}

bool Stack::isEmpty()
{
    return top == -1;
}

bool Stack::isFull()
{
    return top == size - 1;
}

void Stack::push()
{
    if (isFull())
    {
        cout << "Stack is full!" << endl;
    }
    else
    {
        int element;
        cout << "Enter the element to be pushed in stack: ";
        cin >> element;
        stackArr[++top] = element;
        cout << "Element " << stackArr[top] << " pushed at " << top << " position" << endl;
    }
}

void Stack::pop()
{
    if (isEmpty())
    {
        cout << "Stack is empty!" << endl;
    }
    else
    {
        cout << "Element " << stackArr[top] << " popped from " << top << " position" << endl;
        stackArr[top--] = 0;
    }
}

void Stack::display()
{
    for (int i = 0; i <= top; i++)
    {
        cout << stackArr[i] << " ";
    }
    cout << endl;
}

int main()
{
    Stack stack;
    int choice;

    do
    {
        cout << "Choose an operation:" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Display" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            stack.push();
            break;
        case 2:
            stack.pop();
            break;
        case 3:
            stack.display();
            break;
        case 4:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
