#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

ofstream fout("mooyomooyo.out");
ifstream fin("mooyomooyo.in");

void FloodFill(const vector<vector<int> >& Game, vector<vector<bool> >& Visited, vector<simps>& ConnectedCells, const int N, const int x, const int y) {
    Visited[y][x] = true;
    ConnectedCells.push_back({x, y});
    if (x > 0 and (not Visited[y][x - 1] and Game[y][x - 1] == Game[y][x])) FloodFill(Game, Visited, ConnectedCells, N, x - 1, y);
    if (y > 0 and (not Visited[y - 1][x] and Game[y - 1][x] == Game[y][x])) FloodFill(Game, Visited, ConnectedCells, N, x, y - 1);
    if (x < 9 and (not Visited[y][x + 1] and Game[y][x + 1] == Game[y][x])) FloodFill(Game, Visited, ConnectedCells, N, x + 1, y);
    if (y < N - 1 and (not Visited[y + 1][x] and Game[y + 1][x] == Game[y][x])) FloodFill(Game, Visited, ConnectedCells, N, x, y + 1);
    return;
}

void Gravity(vector<vector<int> >& Game, const int N) {
    vector<vector<int> > VerticalGame;
    for (int x = 0; x < 10; x++) {
        int Count = 0;
        vector<int> Column(N);
        for (int y = N - 1; y >= 0; y--) {
            if (Game[y][x] != 0) {
                Column[Count] = Game[y][x];
                Count++;
            }
        }
        VerticalGame.push_back(Column);
    }
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < 10; x++) Game[y][x] = VerticalGame[x][N - y - 1];
    }
    return;
}

bool DestroyCells(vector<vector<int> >& Game, const int N, const int K) {
    bool Changed = false;
    vector<vector<bool> > Visited;
    for (int i = 0; i < N; i++) {
        vector<bool> Row(10);
        Visited.push_back(Row);
    }
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < 10; x++) {
            if (not Visited[y][x] and Game[y][x] != 0) {
                vector<simps> ConnectedCells;
                FloodFill(Game, Visited, ConnectedCells, N, x, y);
                if (ConnectedCells.size() >= K) {
                    Changed = true;
                    for (const simps& s : ConnectedCells) Game[s.second][s.first] = 0;
                }
            }
        }
    }
    if (not Changed) return false;
    Gravity(Game, N);
    return true;
}

int main() {
    int N, K;
    vector<vector<int> > Game;
    fin >> N >> K;
    for (int i = 0; i < N; i++) {
        string Row;
        fin >> Row;
        Game.push_back({});
        for (char c : Row) Game[i].push_back(c - '0');
    }
    Gravity(Game, N);
    while (true) {
        if (not DestroyCells(Game, N, K)) break;
    }
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < 10; x++) fout << Game[y][x];
        fout << "\n";
    }
    return 0;
}
