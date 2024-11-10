#include <iostream>
#include <vector>
using namespace std;

void computeFailureFunction(const string& pattern, vector<int>& f) {
    int m = pattern.length();
    f[0] = 0;
    int j = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[j]) {
            j++;
            f[i] = j;
            i++;
        } else {
            if (j != 0) {
                j = f[j - 1];
            } else {
                f[i] = 0;
                i++;
            }
        }
    }
}

void KMPsearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> f(m);
    computeFailureFunction(pattern, f);

    int i = 0;
    int j = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = f[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = f[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text = "abacaabaccabacabaabb";
    string pattern = "abacab";

    KMPsearch(text, pattern);

    return 0;
}
