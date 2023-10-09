#include <iostream>
using namespace std;

class node
{
public:
    int data;
    node *next;

    node(int val)
    {
        data = val;
        next = nullptr;
    }
};

class sll
{
public:
    node *head;

    sll()
    {
        head = nullptr;
    }

    void insert(int val)
    {
        node *n = new node(val);

        if (head == nullptr)
        {
            head = n;
        }
        else
        {
            node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = n;
        }
    }

    void search(int val)
    {
        node *temp = head;
        int count = 1;
        while (temp->next != nullptr)
        {
            if (temp->data == val)
            {
                cout << "element found at position " << count << endl;
                return;
            }
            temp = temp->next;
            count++;
        }
        cout << "Node no found" << endl;
    }

    node *reverse(node *head)
    {
        if (head == NULL || head->next == NULL)
            return head;

        node *rev = reverse(head->next);
        head->next->next = head;
        head->next = nullptr;

        return rev;
    }

    void sort()
    {
        node *first = head;
        node *second = nullptr;

        while (first != nullptr)
        {
            second = first->next;

            while (second != nullptr)
            {
                if (first->data > second->data)
                {
                    int swap = first->data;
                    first->data = second->data;
                    second->data = swap;
                }
                second = second->next;
            }
            first = first->next;
        }
    }
    void merge(sll s1)
    {
        node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = s1.head;
    }

    void display()
    {
        node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

int main()
{
    sll list1, list2, list3, list4, list5;

    int choice, value, search_val;

    do
    {
        cout << "\n\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Reverse\n";
        cout << "4. Sort\n";
        cout << "5. Merge\n";
        cout << "6. Display\n";
        cout << "7. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the value to be inserted: ";
            cin >> value;
            list1.insert(value);
            break;

        case 2:
            cout << "Enter the value to be searched: ";
            cin >> search_val;
            list1.search(search_val);
            break;

        case 3:
            list1.head = list1.reverse(list1.head);
            cout << "Linked List has been reversed" << endl;
            break;

        case 4:
            list1.sort();
            cout << "Linked List has been sorted" << endl;
            break;

        case 5:
            cout << "Enter the values of the second linked list: " << endl;

            for (int i = 0; i < 5; i++)
            {
                cin >> value;
                list2.insert(value);
            }

            list1.merge(list2);
            cout << "The two linked lists have been merged" << endl;
            break;

        case 6:
            list1.display();
            break;

        case 7:
            exit(0);

        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 7);

    return 0;
}
