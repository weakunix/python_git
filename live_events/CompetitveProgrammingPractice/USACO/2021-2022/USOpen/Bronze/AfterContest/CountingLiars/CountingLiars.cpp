#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int N, MinLie = 1000;
    vector<int> LessThan, GreaterThan;
    set<int> Positions;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int p;
        char c;
        cin >> c >> p;
        if (c == 'L') LessThan.push_back(p);
        else GreaterThan.push_back(p);
        Positions.insert(p);
    }
    for (int i : Positions) {
        int CurLie = 0;
        for (int j : LessThan) {
            if (j < i) CurLie++;
        }
        for (int j : GreaterThan) {
            if (j > i) CurLie++;
        }
        MinLie = min(CurLie, MinLie);
    }
    cout << MinLie << "\n";
    return 0;
}
