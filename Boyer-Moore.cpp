#include <iostream>
#include <string>

using namespace std;

// The preprocessing function for Boyer Moore's
void preprocessBadChar(const string& pat, int badChar[]) {
    int m = pat.size();
    for (int i = 0; i < 1000; ++i)
        badChar[i] = -1; // initialize all entries to -1

    for (int i = 0; i < m; ++i)
        badChar[static_cast<int>(pat[i])] = i;
}

// Boyer-Moore search algorithm
void BoyerMoore(const string& text, const string& pat) {
    int n = text.size();
    int m = pat.size();

    int badChar[1000];
    preprocessBadChar(pat, badChar);

    int shift = 0; // shift of the pattern with respect to text
    while (shift <= (n - m)) {
        int j = m - 1;

        // Reduce j while characters of pattern and text are matching
        while (j >= 0 && pat[j] == text[shift + j])
            --j;

        // When pattern is found
        if (j < 0) {
            cout << "Pattern found at index " << shift << endl;
            if (shift + m < n) {
                shift += m - badChar[static_cast<int>(text[shift + m])];
            } else {
                shift += 1;
            }
        } else {
            // Shift the pattern so that the bad character in text aligns with the last occurrence of it in pattern
            shift += max(1, j - badChar[static_cast<int>(text[shift + j])]);
        }
    }
}

int main() {
    string text = "I enjoy learning CPT212 because it is so fun"; //initialize text
    string pat = "enjoy";                     //initialize pattern/word to be search

    BoyerMoore(text, pat);

    return 0;
}


