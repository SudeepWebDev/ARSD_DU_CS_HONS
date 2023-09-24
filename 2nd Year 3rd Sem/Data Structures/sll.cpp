#include <iostream>

using namespace std;

class Node
{
private:
public:
    int data;
    Node *next;
    Node();
};

Node::Node()
{
    next = NULL;
}

class SLL
{
private:
    Node *head;

public:
    SLL();
    void insert_at_beg(int);
    void insert_at_loc(int num, int position);
    void insert_at_end(int);

    void delete_at_beg();
    void delete_at_loc(int position);
    void delete_at_end();

    void display();
};

SLL::SLL()
{
    head = NULL;
}

void SLL::insert_at_beg(int num)
{
    Node * newNode = new Node();
    newNode -> data = num;
    newNode -> next = head;
    head = newNode;
}
void SLL::insert_at_loc(int num, int position)
{
    Node *newNode = new Node();
    newNode->data = num;

    if (position == 1) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node *prev = head;
    for (int i = 1; i < position - 1 && prev != nullptr; i++) {
        prev = prev->next;
    }

    if (prev == nullptr) {
        cout << "Position out of range." << endl;
        return;
    }

    newNode->next = prev->next;
    prev->next = newNode;
}

void SLL::insert_at_end(int num)
{
    Node *newNode = new Node();
    newNode->data = num;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node *temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;
}

void SLL::delete_at_beg()
{
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }

    Node *temp = head;
    head = head->next;
    delete temp;
}

void SLL::delete_at_loc(int position)
{
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }

    if (position == 1) {
        delete_at_beg();
        return;
    }

    Node *prev = head;
    Node *curr = head->next;

    for (int i = 2; curr != nullptr && i < position; i++) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        cout << "Position out of range." << endl;
        return;
    }

    prev->next = curr->next;
    delete curr;
}

void SLL::delete_at_end()
{
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }

    if (head->next == nullptr) {
        delete_at_beg();
        return;
    }

    Node *prev = head;
    Node *curr = head->next;

    while (curr->next != nullptr) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = nullptr;
    delete curr;
}

void SLL::display()
{
    Node *current = head;

    if (current == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    cout << "Linked List: ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main()
{
    SLL myList;
    int choice, num, position;

    do {
        cout << "Menu:" << endl;
        cout << "1. Insert at the beginning" << endl;
        cout << "2. Insert at a specific location" << endl;
        cout << "3. Insert at the end" << endl;
        cout << "4. Delete at the beginning" << endl;
        cout << "5. Delete at a specific location" << endl;
        cout << "6. Delete at the end" << endl;
        cout << "7. Display" << endl;
        cout << "8. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the number to insert at the beginning: ";
                cin >> num;
                myList.insert_at_beg(num);
                break;
            case 2:
                cout << "Enter the number to insert: ";
                cin >> num;
                cout << "Enter the position to insert at: ";
                cin >> position;
                myList.insert_at_loc(num, position);
                break;
            case 3:
                cout << "Enter the number to insert at the end: ";
                cin >> num;
                myList.insert_at_end(num);
                break;
            case 4:
                myList.delete_at_beg();
                break;
            case 5:
                cout << "Enter the position to delete: ";
                cin >> position;
                myList.delete_at_loc(position);
                break;
            case 6:
                myList.delete_at_end();
                break;
            case 7:
                cout << "Linked List: ";
                myList.display();
                break;
            case 8:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}
