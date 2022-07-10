#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

int main() {
    int N;
    unordered_set<string> Words;
    cin >> N;
    vector<vector<string> > Blocks;
    for (int i = 0; i < 4; i++) {
        vector<string> CurBlock(7);
        Blocks.push_back(CurBlock);
        for (int j = 0; j < 6; j++) {
            char c;
            cin >> c;
            Blocks[i][j] += c;
        }
    }
    for (string a : Blocks[0]) {
        for (string b : Blocks[1]) {
            for (string c : Blocks[2]) {
                for (string d : Blocks[3]) {
                    string CurWord = a + b + c + d;
                    sort(all(CurWord));
                    Words.insert(CurWord);
                }
            }
        }
    }
    for (int i = 0; i < N; i++) {
        string TarWord;
        cin >> TarWord;
        sort(all(TarWord));
        if (Words.count(TarWord) > 0) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
