#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("snowboots.out");
ifstream fin("snowboots.in");

bool AddRow(vector<vector<int> >& CanReach, const vector<int>& Tiles, const int N, const int Depth, const int Dist, const int Row) {
    int Prev = 0;
    CanReach[Row][0] = 2;
    for (int i = 1; i < N; i++) {
        if (Tiles[i] <= Depth) {
            if (i - Prev <= Dist or (Row > 0 and CanReach[Row - 1][i] > 0)) {
                CanReach[Row][i] = 2;
                Prev = i;
            }
        }
        else {
            if (Row > 0 and CanReach[Row - 1][i] > 0) CanReach[Row][i] = 1;
        }
    }
    return CanReach[Row].back() == 2;
}

int main() {
    int N, B;
    vector<vector<int> > CanReach;
    fin >> N >> B;
    vector<int> Tiles(N), SnowDepths(B), Dist(B);
    for (int i = 0; i < N; i++) fin >> Tiles[i];
    for (int i = 0; i < B; i++) {
        vector<int> Row(N);
        CanReach.push_back(Row);
        fin >> SnowDepths[i];
        fin >> Dist[i];
    }
    for (int i = 0; i < B; i++) {
        if (AddRow(CanReach, Tiles, N, SnowDepths[i], Dist[i], i)) {
            fout << i << "\n";
            return 0;
        }
    }
    return 1;
}
