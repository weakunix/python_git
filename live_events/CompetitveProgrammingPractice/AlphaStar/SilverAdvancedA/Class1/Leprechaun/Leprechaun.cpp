#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int BestSum(const vector<int>& Line, const int N) {
    int Best = -1e6;
    for (int i = 0; i < N; i++) {
        int Lowest = 0;
        vector<int> Pre = {0};
        for (int j = 0; j < N; j++) Pre.push_back(Line[(j + i) % N] + Pre.back());
        for (int j = 1; j < Pre.size(); j++) {
            int Cur = Pre[j];
            Best = max(Cur - Lowest, Best);
            Lowest = min(Cur, Lowest);
        }
    }
    return Best;
}

int main() {
    int N, Best = -1e6;
    vector<vector<int> > Grid;
    cin >> N;
    for (int y = 0; y < N; y++) {
        vector<int> Row(N);
        Grid.push_back(Row);
        for (int x = 0; x < N; x++) cin >> Grid[y][x];
    }
    for (int y = 0; y < N; y++) {
        vector<int> Row;
        for (int x = 0; x < N; x++) Row.push_back(Grid[y][x]);
        Best = max(BestSum(Row, N), Best);
    }
    for (int x = 0; x < N; x++) {
        vector<int> Col;
        for (int y = 0; y < N; y++) Col.push_back(Grid[y][x]);
        Best = max(BestSum(Col, N), Best);
    }
    for (int i = 0; i < N; i++) {
        vector<int> Diag;
        int x = i, y = 0;
        for (int j = 0; j < N; j++) {
            Diag.push_back(Grid[y % N][x % N]);
            x++;
            y++;
        }
        Best = max(BestSum(Diag, N), Best);
    }
    for (int i = 0; i < N; i++) {
        vector<int> RevDiag;
        int x = i, y = N;
        for (int j = 0; j < N; j++) {
            RevDiag.push_back(Grid[y % N][x % N]);
            x++;
            y--;
        }
        Best = max(BestSum(RevDiag, N), Best);
    }
    cout << Best << "\n";
    return 0;
}
