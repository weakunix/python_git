#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_set>

using namespace std;

typedef pair<string, int> psi;

int Bfs(const unordered_set<string>& Dict, const string Start, const string End) {
    queue<psi> WordQueue;
    unordered_set<string> VisitedWords;
    WordQueue.push({Start, 0});
    VisitedWords.insert(Start);
    while (WordQueue.size() > 0) {
        string CurWord = WordQueue.front().first;
        int CurMoves = WordQueue.front().second;
        WordQueue.pop();
        if (CurWord == End) return CurMoves;
        for (int i = 0; i < CurWord.size(); i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                string NewString = CurWord.substr(0, i) + c + CurWord.substr(i + 1, CurWord.size() - i - 1);
                if (Dict.count(NewString) > 0 and VisitedWords.count(NewString) == 0) {
                    VisitedWords.insert(NewString);
                    WordQueue.push({NewString, CurMoves + 1});
                }
            }
        }
    }
    return -1;
}

int main() {
    string Start, End, CurDictWord;
    unordered_set<string> Dict;
    cin >> Start >> End;
    while (cin >> CurDictWord) Dict.insert(CurDictWord);
    cout << Bfs(Dict, Start, End) << "\n";
    return 0;
}
