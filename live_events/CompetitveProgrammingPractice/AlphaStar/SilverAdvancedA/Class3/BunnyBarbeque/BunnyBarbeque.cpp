#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

#define all(v) v.begin(), v.end()

int AllOneType(const vector<pii>& Rabbits, const int N) {
    int Best = 0, First = Rabbits[0].first, CurType = Rabbits[0].second;
    for (int i = 0; i < N; i++) {
        if (Rabbits[i].second != CurType) {
            CurType = Rabbits[i].second;
            Best = max(Rabbits[i - 1].first - First, Best);
            First = Rabbits[i].first;
        }
    }
    Best = max(Rabbits.back().first - First, Best);
    return Best;
}

int main() {
    int N, Best = 0;
    vector<pii> Rabbits;
    unordered_map<int, int> FirstOccurence;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int x;
        char c;
        cin >> x >> c;
        if (c == 'S') Rabbits.push_back({x, 1});
        else Rabbits.push_back({x, -1});
    }
    sort(all(Rabbits));
    Best = AllOneType(Rabbits, N);
    for (int i = 0; i < N; i++) {
        if (i > 0) Rabbits[i].second += Rabbits[i - 1].second;
    }
    FirstOccurence[0] = Rabbits[0].first;
    for (int i = 0; i < N; i++) {
        if (FirstOccurence.count(Rabbits[i].second) == 0) {
            if (i < N - 1) FirstOccurence[Rabbits[i].second] = Rabbits[i + 1].first;
        }
        else Best = max(Rabbits[i].first - FirstOccurence[Rabbits[i].second], Best);
    }
    cout << Best << "\n";
    return 0;
}
