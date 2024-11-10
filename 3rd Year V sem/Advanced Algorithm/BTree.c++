#include <iostream>
using namespace std;

class BTreeNode {
public:
    bool leaf;
    int keyTally;
    int keys[4]; // M-1 = 5-1 = 4 keys
    BTreeNode* pointers[5]; // M = 5 pointers

    BTreeNode(bool leaf);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);
    void traverse();
    BTreeNode* search(int k);
};

BTreeNode::BTreeNode(bool leaf) {
    this->leaf = leaf;
    this->keyTally = 0;
    for (int i = 0; i < 5; i++) {
        this->pointers[i] = nullptr;
    }
}

void BTreeNode::insertNonFull(int k) {
    int i = keyTally - 1;

    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        keyTally++;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (pointers[i + 1]->keyTally == 4) { // M - 1 = 4
            splitChild(i + 1, pointers[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        pointers[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->leaf);
    z->keyTally = 2; // M / 2 - 1 = 5 / 2 - 1 = 2

    for (int j = 0; j < 2; j++)
        z->keys[j] = y->keys[j + 3]; // M / 2 = 3

    if (!y->leaf) {
        for (int j = 0; j < 3; j++)
            z->pointers[j] = y->pointers[j + 3];
    }

    y->keyTally = 2;
    for (int j = keyTally; j >= i + 1; j--)
        pointers[j + 1] = pointers[j];

    pointers[i + 1] = z;
    for (int j = keyTally - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[2];
    keyTally++;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keyTally; i++) {
        if (!leaf)
            pointers[i]->traverse();
        cout << " " << keys[i];
    }

    if (!leaf)
        pointers[i]->traverse();
}

BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < keyTally && k > keys[i])
        i++;

    if (i < keyTally && keys[i] == k)
        return this;

    if (leaf)
        return nullptr;

    return pointers[i]->search(k);
}

class BTree {
    BTreeNode* root;

public:
    BTree() {
        root = new BTreeNode(true);
    }

    void traverse() {
        if (root != nullptr)
            root->traverse();
    }

    BTreeNode* search(int k) {
        if (root == nullptr)
            return nullptr;
        else
            return root->search(k);
    }

    void insert(int k);
};

void BTree::insert(int k) {
    if (root->keyTally == 4) { // M - 1 = 4
        BTreeNode* s = new BTreeNode(false);
        s->pointers[0] = root;
        s->splitChild(0, root);
        int i = 0;
        if (s->keys[0] < k)
            i++;
        s->pointers[i]->insertNonFull(k);
        root = s;
    } else
        root->insertNonFull(k);
}

int main() {
    BTree t;

    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Traversal of the constructed B-Tree is:";
    t.traverse();

    int k = 6;
    cout << "\nSearching for " << k << ": " << (t.search(k) ? "Present" : "Not Present");

    k = 15;
    cout << "\nSearching for " << k << ": " << (t.search(k) ? "Present" : "Not Present");

    return 0;
}
