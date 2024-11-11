#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class SuffixTrieNode {
public:
    unordered_map<char, SuffixTrieNode*> children;
    vector<int> indexes;

    void insertSuffix(const string& suffix, int index) {
        indexes.push_back(index);
        if (!suffix.empty()) {
            char firstChar = suffix[0];
            if (children.find(firstChar) == children.end()) {
                children[firstChar] = new SuffixTrieNode();
            }
            children[firstChar]->insertSuffix(suffix.substr(1), index);
        }
    }
};

class SuffixTrie {
public:
    SuffixTrieNode* root;

    SuffixTrie(const string& text) {
        root = new SuffixTrieNode();
        for (int i = 0; i < text.length(); ++i) {
            root->insertSuffix(text.substr(i), i);
        }
    }

    vector<int> search(const string& pattern) {
        SuffixTrieNode* currentNode = root;
        for (char ch : pattern) {
            if (currentNode->children.find(ch) == currentNode->children.end()) {
                return {};
            }
            currentNode = currentNode->children[ch];
        }
        return currentNode->indexes;
    }
};

int main() {
    string text = "minimize";
    SuffixTrie trie(text);

    string pattern = "ie";
    vector<int> result = trie.search(pattern);

    if (!result.empty()) {
        cout << "Pattern found at indexes: ";
        for (int index : result) {
            cout << index << " ";
        }
        cout << endl;
    } else {
        cout << "Pattern not found" << endl;
    }

    return 0;
}
