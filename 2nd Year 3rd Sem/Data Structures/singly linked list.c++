#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node()
    {
        next = NULL;
    };
};

class SLL
{
private:
    Node *top;

public:
    SLL()
    {
        top = NULL;
    };
    void push(int num)
    {
        Node *newNode = new Node();
        newNode->data = num;
        newNode->next = top;
        top = newNode;
    };
    void pop()
    {
        if (top == nullptr)
        {
            cout << "Underflow: Stack is empty!" << endl;
            return;
        }

        Node *temp = top;
        top = top->next;
        delete temp;
    }
    void Top()
    {
        if (top == nullptr)
        {
            cout << "Underflow: Stack is empty!" << endl;
            return;
        }

        cout<<top->data<<endl;
    }
    void display()
    {
        Node *current = top;

        if (current == NULL)
        {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "Stack: ";
        while (current != NULL)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    };
};

int main()
{
    SLL stack;
    int choice, num;

    do
    {
        cout << "Menu:" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Top" << endl;
        cout << "4. Display" << endl;
        cout << "5. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the number to insert in Stack: ";
            cin >> num;
            stack.push(num);
            break;
        case 2:
            stack.pop();
            break;
        case 3:
            cout << "Top: ";
            stack.Top();
            cout<<endl;
            break;
        case 4:
            stack.display();
            break;
        case 5:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 5);

    return 0;
}
