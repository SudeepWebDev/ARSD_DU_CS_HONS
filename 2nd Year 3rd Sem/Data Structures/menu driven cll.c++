#include <iostream>
using namespace std;
class CNode
{
private:
    int data;
    CNode *next;
    friend class CLL;
};

class CLL
{
private:
    CNode *cursor;

public:
    CLL();
    ~CLL();
    bool empty() const;
    const int front() const;
    const int back() const;
    void advance();
    void add(const int);
    void remove();
    void display() const;
};

CLL::CLL()
{
    cursor = nullptr;
}
CLL::~CLL()
{
    while (!empty())
    {
        remove();
    }
}

bool CLL::empty() const
{
    return (cursor == nullptr);
}

const int CLL::front() const
{
    return (cursor->next->data);
}
const int CLL::back() const
{
    return (cursor->data);
}

void CLL::advance()
{
    cursor = cursor->next;
}

void CLL::add(const int num)
{
    CNode *newNode = new CNode();
    newNode->data = num;
    if (empty())
    {
        newNode->next = newNode;
        cursor = newNode;
    }
    else
    {
        newNode->next = cursor->next;
        cursor->next = newNode;
    }
}

void CLL::remove()
{
    CNode *old = cursor->next;
    cout << "Deleted Node is: " << old->data;
    if (cursor == old)
    {
        cursor = nullptr;
    }
    else
    {
        cursor->next = old->next;
    }
    delete (old);
}

void CLL::display() const
{
    if (empty())
    {
        cout << "List is empty." << endl;
        return;
    }

    CNode *current = cursor->next;

    while (current != cursor)
    {
        cout << current->data << " ";
        current = current->next;
    }

    cout << current->data << endl;
}

int main()
{
    CLL circularList;

    int choice, num;

    do
    {
        cout << "\nCircular Linked List Menu:\n";
        cout << "1. Add Element\n";
        cout << "2. Remove Element\n";
        cout << "3. Display Front Element\n";
        cout << "4. Display Back Element\n";
        cout << "5. Move to Next Element\n";
        cout << "6. Display \n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the element to add: ";
            cin >> num;
            circularList.add(num);
            break;
        case 2:
            circularList.remove();
            break;
        case 3:
            if (!circularList.empty())
                cout << "Front element: " << circularList.front() << endl;
            else
                cout << "List is empty\n";
            break;
        case 4:
            if (!circularList.empty())
                cout << "Back element: " << circularList.back() << endl;
            else
                cout << "List is empty\n";
            break;
        case 5:
            circularList.advance();
            break;
        case 6:
            circularList.display();
            break;

        case 0:
            cout << "Exiting the program\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
