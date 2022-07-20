#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_map>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, int> piipi;

int Bfs(const vector<vector<char> >& Maze, const unordered_map<char, pii>& FirstPortal, const unordered_map<char, pii>& SecondPortal, const int N, const int M, const int StartX, const int StartY, const int EndX, const int EndY) {
    int DirX[4] = {1, 0, -1, 0}, DirY[4] = {0, 1, 0, -1};
    vector<vector<bool> > Visited;
    for (int i = 0; i < N; i++) {
        vector<bool> Row(M);
        Visited.push_back(Row);
    }
    queue<piipi> GridQueue;
    GridQueue.push({{StartX, StartY}, 0});
    Visited[StartY][StartX] = true;
    while (not GridQueue.empty()) {
        int CurX = GridQueue.front().first.first, CurY = GridQueue.front().first.second, Moves = GridQueue.front().second;
        GridQueue.pop();
        if (CurX == EndX and CurY == EndY) return Moves;
        for (int i = 0; i < 4; i++) {
            int NewX = CurX + DirX[i], NewY = CurY + DirY[i];
            if ((NewX >= 0 and NewX < M) and (NewY >= 0 and NewY < N)) {
                char CurGrid = Maze[NewY][NewX];
                if (not Visited[NewY][NewX] and CurGrid != '#') {
                    Visited[NewY][NewX] = true;
                    if (CurGrid != '.' and (CurGrid != '@' and CurGrid != '=')) {
                        Visited[NewY][NewX] = false;
                        pii Coord = {NewX, NewY};
                        if (FirstPortal.at(CurGrid) == Coord) {
                            NewX = SecondPortal.at(CurGrid).first;
                            NewY = SecondPortal.at(CurGrid).second;
                        }
                        else {
                            NewX = FirstPortal.at(CurGrid).first;
                            NewY = FirstPortal.at(CurGrid).second;
                        }
                    }
                    GridQueue.push({{NewX, NewY}, Moves + 1});
                }
            }
        }
    }
    return -1;
}

int main() {
    int N, M, StartX, StartY, EndX, EndY;
    unordered_map<char, pii> FirstPortal, SecondPortal;
    cin >> N >> M;
    vector<vector<char> > Maze(N);
    for (int y = 0; y < N; y++) {
        string Row;
        cin >> Row;
        for (int x = 0; x < M; x++) {
            char CurGrid = Row[x];
            Maze[y].push_back(CurGrid);
            if (CurGrid == '@') {
                StartX = x;
                StartY = y;
            }
            else if (CurGrid == '=') {
                EndX = x;
                EndY = y;
            }
            else if (CurGrid != '.' and CurGrid != '#') {
                if (FirstPortal.count(CurGrid) == 0) FirstPortal[CurGrid] = {x, y};
                else SecondPortal[CurGrid] = {x, y};
            }
        }
    }
    cout << Bfs(Maze, FirstPortal, SecondPortal, N, M, StartX, StartY, EndX, EndY) << "\n";
    return 0;
}
