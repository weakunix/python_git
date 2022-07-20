#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

bool IsPossibleComb(const vector<string>& Striped, const vector<string>& Solid, const int i, const int j, const int k) {
    unordered_set<string> StripedGenomes;
    for (string s : Striped) {
        string CurGenome;
        CurGenome += s[i];
        CurGenome += s[j];
        CurGenome += s[k];
        StripedGenomes.insert(CurGenome);
    }
    for (string s : Solid) {
        string CurGenome;
        CurGenome += s[i];
        CurGenome += s[j];
        CurGenome += s[k];
        if (StripedGenomes.count(CurGenome) > 0) return false;
    }
    return true;
}

int main() {
    int N, M, Count = 0;
    cin >> N >> M;
    vector<string> Striped(N), Solid(N);
    for (int i = 0; i < N; i++) cin >> Striped[i];
    for (int i = 0; i < N; i++) cin >> Solid[i];
    for (int i = 0; i < M - 2; i++) {
        for (int j = i + 1; j < M - 1; j++) {
            for (int k = j + 1; k < M; k++) {
                if (IsPossibleComb(Striped, Solid, i, j, k)) Count++;
            }
        }
    }
    cout << Count << "\n";
    return 0;
}
