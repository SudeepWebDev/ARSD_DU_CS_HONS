#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class TreeNode {
public:
    int data;
    vector<TreeNode*> children;

    TreeNode(int val) {
        data = val;
    }
};

class Tree {
public:
    TreeNode* root;

    Tree(int rootVal) {
        root = new TreeNode(rootVal);
    }

    void insert(TreeNode* parent, int childVal) {
        if (!parent) return;
        TreeNode* childNode = new TreeNode(childVal);
        parent->children.push_back(childNode);
    }

    bool search(TreeNode* node, int val) {
        if (!node) return false;
        if (node->data == val) return true;
        
        for (TreeNode* child : node->children) {
            if (search(child, val)) 
                return true;
        }
        return false;
    }

    void printTree(TreeNode* node, int level = 0) {
        if (!node) return;
        
        for (int i = 0; i < level; ++i) cout << "  ";  // Indentation for hierarchy
        cout << "|--" << node->data << endl;
        
        for (TreeNode* child : node->children) {
            printTree(child, level + 1);
        }
    }
};

int main() {
    Tree tree(1);  
    tree.insert(tree.root, 2);
    tree.insert(tree.root, 3);
    tree.insert(tree.root->children[0], 4);
    tree.insert(tree.root->children[0], 5);
    tree.insert(tree.root->children[1], 6);
    tree.insert(tree.root->children[1], 7);

    cout << "Tree Structure:" << endl;
    tree.printTree(tree.root);

    cout << "\nSearch for 5: " << (tree.search(tree.root, 5) ? "Found" : "Not Found") << endl;
    cout << "Search for 8: " << (tree.search(tree.root, 8) ? "Found" : "Not Found") << endl;

    return 0;
}
