#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int d) {
        data = d;
        next = nullptr;
    }
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    bool isEmpty() {
        return (front == nullptr && rear == nullptr);
    }

    void enqueue(int x) {
        Node* newNode = new Node(x);
        if (isEmpty()) {
            front = newNode;
            rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    int dequeue() {
        if (isEmpty()) {
            throw "Queue is empty";
        }
        else {
            int x = front->data;
            Node* temp = front;
            front = front->next;
            if (front == nullptr) {
                rear = nullptr;
            }
            delete temp;
            return x;
        }
    }

    int peek() {
        if (isEmpty()) {
            throw "Queue is empty";
        }
        else {
            return front->data;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
        }
        else {
            cout << "Queue: ";
            Node* temp = front;
            while (temp != nullptr) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

int main() {
    Queue myQueue;
    int choice, element;

    while (true) {
        cout << "Queue Operations Menu:" << endl;
        cout << "1. Enqueue" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Peek" << endl;
        cout << "4. Display" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter element to enqueue: ";
                cin >> element;
                myQueue.enqueue(element);
                break;
            case 2:
                try {
                    element = myQueue.dequeue();
                    cout << "Dequeued element: " << element << endl;
                }
                catch (const char* msg) {
                    cout << msg << endl;
                }
                break;
            case 3:
                try {
                    element = myQueue.peek();
                    cout << "Front element: " << element << endl;
                }
                catch (const char* msg) {
                    cout << msg << endl;
                }
                break;
            case 4:
                myQueue.display();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return 0;
}
