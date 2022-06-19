#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> simps;

ofstream fout("ccski.out");
ifstream fin("ccski.in");

void FloodFill(const vector<vector<int> >& Grid, vector<vector<bool> >& Visited, const int M, const int N, const int x, const int y, const int D) {
    Visited[y][x] = true;
    if (x > 0 and not Visited[y][x - 1]) {
        if (abs(Grid[y][x] - Grid[y][x - 1]) <= D) FloodFill(Grid, Visited, M, N, x - 1, y, D);
    }
    if (x < N - 1 and not Visited[y][x + 1]) {
        if (abs(Grid[y][x] - Grid[y][x + 1]) <= D) FloodFill(Grid, Visited, M, N, x + 1, y, D);
    }
    if (y > 0 and not Visited[y - 1][x]) {
        if (abs(Grid[y][x] - Grid[y - 1][x]) <= D) FloodFill(Grid, Visited, M, N, x, y - 1, D);
    }
    if (y < M - 1 and not Visited[y + 1][x]) {
        if (abs(Grid[y][x] - Grid[y + 1][x]) <= D) FloodFill(Grid, Visited, M, N, x, y + 1, D);
    }
    return;
}

bool IsValidDifficulty(const vector<vector<int> >& Grid, const vector<simps>& Waypoints, const int M, const int N, const int D) {
    vector<vector<bool> > Visited(M);
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) Visited[y].push_back(false);
    }
    FloodFill(Grid, Visited, M, N, Waypoints[0].first, Waypoints[0].second, D);
    for (const simps& s : Waypoints) {
        if (not Visited[s.second][s.first]) return false;
    }
    return true;
}

int main() {
    int M, N, Low = 0, High = 1e9;
    vector<simps> Waypoints;
    fin >> M >> N;
    vector<vector<int> > Grid(M);
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            int Elevation;
            fin >> Elevation;
            Grid[y].push_back(Elevation);
        }
    }
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            bool IsWaypoint;
            fin >> IsWaypoint;
            if (IsWaypoint) Waypoints.push_back({x, y});
        }
    }
    while (Low < High) {
        int Mid = Low + (High - Low) / 2;
        if (IsValidDifficulty(Grid, Waypoints, M, N, Mid)) High = Mid;
        else Low = Mid + 1;
    }
    assert(Low == High);
    fout << Low << "\n";
    return 0;
}
