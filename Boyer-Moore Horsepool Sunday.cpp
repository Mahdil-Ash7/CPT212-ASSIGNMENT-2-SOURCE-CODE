#include <iostream>
#include <array>
#include <string>

using namespace std;

// Function to create the bad character heuristic table
void badCharHeuristic(const string &pattern, array<int, 256> &badChar) {
    int m = pattern.size();
    fill(badChar.begin(), badChar.end(), m + 1); // Initialize all occurrences as pattern length + 1

    // Fill the actual value of the last occurrence of a character
    for (int i = 0; i < m; i++) {
        badChar[static_cast<int>(pattern[i])] = m - i;
    }
}

// Boyer-Moore-Horspool-Sunday algorithm for pattern searching
void boyerMooreHorspoolSundaySearch(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();

    array<int, 256> badChar;
    badCharHeuristic(pattern, badChar);

    int s = 0; // s is the shift of the pattern with respect to text

    while (s <= (n - m)) {
        int j = 0;

        // Keep increasing index j of pattern while characters of pattern and text are matching at this shift s
        while (j < m && pattern[j] == text[s + j]) {
            j++;
        }

        // If the pattern is present at the current shift, then index j will become equal to the pattern length
        if (j == m) {
            cout << "Pattern found at index " << s << endl;
        }

        // Shift the pattern to align the next character in text with the pattern
        if (s + m < n) {
            s += badChar[static_cast<int>(text[s + m])];
        } else {
            break;
        }
    }
}

int main() {
    string text = "I enjoy learning CPT212 because it is so fun";
    string pattern = "fun";
    boyerMooreHorspoolSundaySearch(text, pattern);
    return 0;
}

