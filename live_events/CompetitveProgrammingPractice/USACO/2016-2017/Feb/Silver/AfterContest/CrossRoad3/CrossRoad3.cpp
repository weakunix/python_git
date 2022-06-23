#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

ofstream fout("countcross.out");
ifstream fin("countcross.in");

bool FloodFill(const vector<vector<bool> >& BlockedFromEast, const vector<vector<bool> >& BlockedFromNorth, vector<vector<bool> >& Visited, const int N, const int TarX, const int TarY, const int x, const int y) {
    if (x == TarX and y == TarY) return true;
    Visited[y][x] = true;
    if (x > 0 and not BlockedFromEast[y][x - 1]) {
        if (not Visited[y][x - 1]) {
            if (FloodFill(BlockedFromEast, BlockedFromNorth, Visited, N, TarX, TarY, x - 1, y)) return true;
        }
    }
    if (y > 0 and not BlockedFromNorth[y - 1][x]) {
        if (not Visited[y - 1][x]) {
            if (FloodFill(BlockedFromEast, BlockedFromNorth, Visited, N, TarX, TarY, x, y - 1)) return true;
        }
    }
    if (x < N - 1 and not BlockedFromEast[y][x]) {
        if (not Visited[y][x + 1]) {
            if (FloodFill(BlockedFromEast, BlockedFromNorth, Visited, N, TarX, TarY, x + 1, y)) return true;
        }
    }
    if (y < N - 1 and not BlockedFromNorth[y][x]) {
        if (not Visited[y + 1][x]) {
            if (FloodFill(BlockedFromEast, BlockedFromNorth, Visited, N, TarX, TarY, x, y + 1)) return true;
        }
    }
    return false;
}

int main() {
    int N, K, R, Ans = 0;
    vector<simps> Cows;
    fin >> N >> K >> R;
    vector<vector<bool> > BlockedFromEast(N), BlockedFromNorth(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            BlockedFromEast[i].push_back(false);
            BlockedFromNorth[i].push_back(false);
        }
    }
    for (int i = 0; i < R; i++) {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        x1--;
        y1--;
        x2--;
        y2--;
        if (x1 == x2) BlockedFromNorth[min(y1, y2)][x1] = true;
        else BlockedFromEast[y1][min(x1, x2)] = true;
    }
    for (int i = 0; i < K; i++) {
        int x, y;
        fin >> x >> y;
        x--;
        y--;
        Cows.push_back({x, y});
    }
    for (int i = 0; i < K - 1; i++) {
        for (int j = i + 1; j < K; j++) {
            vector<vector<bool> > Visited(N);
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) Visited[k].push_back(false);
            }
            if (not FloodFill(BlockedFromEast, BlockedFromNorth, Visited, N, Cows[j].first, Cows[j].second, Cows[i].first, Cows[i].second)) Ans++;
        }
    }
    fout << Ans << "\n";
    return 0;
}
