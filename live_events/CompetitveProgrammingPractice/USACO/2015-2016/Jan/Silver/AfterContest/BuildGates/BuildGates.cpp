#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

ofstream fout("gates.out");
ifstream fin("gates.in");

void LoadBlockedCells(vector<vector<bool> >& BlockedEast, vector<vector<bool> >& BlockedNorth, const string Moves) {
    int x = 1000, y = 1000;
    for (char c : Moves) {
        if (c == 'N') {
            BlockedEast[y][x - 1] = true;
            y++;
        }
        else if (c == 'E') {
            BlockedNorth[y - 1][x] = true;
            x++;
        }
        else if (c == 'S') {
            y--;
            BlockedEast[y][x - 1] = true;
        }
        else {
            x--;
            BlockedNorth[y - 1][x] = true;
        }
    }
    return;
}

void FloodFill(const vector<vector<bool> >& BlockedEast, const vector<vector<bool> >& BlockedNorth, vector<vector<bool> >& Visited, const int FirstX, const int FirstY) {
    vector<simps> NodeQueue = {{FirstX, FirstY}};
    Visited[FirstY][FirstX] = true;
    while (NodeQueue.size() > 0) {
        int x = NodeQueue.back().first, y = NodeQueue.back().second;
        NodeQueue.pop_back();
        if (x > 0 and not BlockedEast[y][x - 1]) {
            if (not Visited[y][x - 1]) {
                Visited[y][x - 1] = true;
                NodeQueue.push_back({x - 1, y});
            }
        }
        if (y > 0 and not BlockedNorth[y - 1][x]) {
            if (not Visited[y - 1][x]) {
                Visited[y - 1][x] = true;
                NodeQueue.push_back({x, y - 1});
            }
        }
        if (x < 1999 and not BlockedEast[y][x]) {
            if (not Visited[y][x + 1]) {
                Visited[y][x + 1] = true;
                NodeQueue.push_back({x + 1, y});
            }
        }
        if (y < 1999 and not BlockedNorth[y][x]) {
            if (not Visited[y + 1][x]) {
                Visited[y + 1][x] = true;
                NodeQueue.push_back({x, y + 1});
            }
        }
    }
    return;
}

int main() {
    int N, ConComp = -1;
    vector<vector<bool> > Visited(2000), BlockedEast(2000), BlockedNorth(2000);
    string Moves;
    fin >> N >> Moves;
    for (int y = 0; y < 2000; y++) {
        for (int x = 0; x < 2000; x++) {
            Visited[y].push_back(false);
            BlockedEast[y].push_back(false);
            BlockedNorth[y].push_back(false);
        }
    }
    LoadBlockedCells(BlockedEast, BlockedNorth, Moves);
    for (int y = 0; y < 2000; y++) {
        for (int x = 0; x < 2000; x++) {
            if (not Visited[y][x]) {
                ConComp++;
                FloodFill(BlockedEast, BlockedNorth, Visited, x, y);
            }
        }
    }
    fout << ConComp << "\n";
    return 0;
}
