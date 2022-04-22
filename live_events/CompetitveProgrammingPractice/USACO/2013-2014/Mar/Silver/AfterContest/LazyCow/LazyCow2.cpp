#include <fstream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

ofstream fout("lazy.out");
ifstream fin("lazy.in");

int main() {
    int N, K, Best = 0;
    vector<vector<int> > Grass, PreG;
    fin >> N >> K;
    for (int y = 0; y <= N; y++) {
        vector<int> NewRow(N + 1), NewPre(N + 1);
        if (y > 0) {
            for (int x = 1; x <= N; x++) {
                int g;
                fin >> g;
                NewRow[x] = g;
                NewPre[x] = g + NewPre[x - 1] + PreG[y - 1][x] - PreG[y - 1][x - 1];
            }
        }
        Grass.push_back(NewRow);
        PreG.push_back(NewPre);
    }
    if (K == 0) {
        for (int y = 1; y <= N; y++) {
            for (int x = 1; x <= N; x++) Best = max(Grass[y][x], Best);
        }
    }
    else if (K == 1) {
        for (int y = 1; y <= N; y++) {
            for (int x = 1; x <= N; x++) {
                int Cur = 0;
                Cur += Grass[y][x] + Grass[y - 1][x] + Grass[y][x - 1];
                if (y + 1 <= N) Cur += Grass[y + 1][x];
                if (x + 1 <= N) Cur += Grass[y][x + 1];
                Best = max(Cur, Best);
            }
        }
    }
    else {
        for (int y = 1; y <= N; y++) {
            for (int x = 1; x <= N; x++) {
                if (x == 3 and y == 3)
                    fout << "";
                int MinX = max(x - K + 2, 1), MinY = max(y - K + 2, 1), MaxX = min(x + K - 2, N), MaxY = min(y + K - 2, N), Cur = PreG[MaxY][MaxX] - PreG[MaxY][MinX - 1] - PreG[MinY - 1][MaxX] + PreG[MinY - 1][MinX - 1];
                set<pair<int, int> > Points = {{x + K - 1, y}, {x + K - 1, y + 1}, {x + K - 1, y - 1}, {x, y + K - 1}, {x + 1, y + K - 1}, {x - 1, y + K - 1}, {x - K + 1, y}, {x - K + 1, y + 1}, {x - K + 1, y - 1}, {x, y - K + 1}, {x + 1, y - K + 1}, {x - 1, y - K + 1}, {x + K, y}, {x, y + K}, {x - K, y}, {x, y - K}}; 
                for (pair<int, int> p : Points) {
                    if (p.first >= 1 and p.first <= N and p.second >= 1 and p.second <= N) Cur += Grass[p.second][p.first];
                }
                Best = max(Cur, Best);
            }
        }
    }
    fout << Best << "\n";
    return 0;
}
