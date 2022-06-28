#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

ofstream fout("multimoo.out");
ifstream fin("multimoo.in");

int SingleCowFloodFill(vector<vector<int> >& Board, vector<vector<bool> >& Visited, const int CurConComp, const int N, const int x, const int y, const int RegionVal) {
    int Count = 1;
    Visited[y][x] = true;
    Board[y][x] = CurConComp;
    if ((x > 0 and not Visited[y][x - 1]) and Board[y][x - 1] == RegionVal) Count += SingleCowFloodFill(Board, Visited, CurConComp, N, x - 1, y, RegionVal);
    if ((y > 0 and not Visited[y - 1][x]) and Board[y - 1][x] == RegionVal) Count += SingleCowFloodFill(Board, Visited, CurConComp, N, x, y - 1, RegionVal);
    if ((x < N - 1 and not Visited[y][x + 1]) and Board[y][x + 1] == RegionVal) Count += SingleCowFloodFill(Board, Visited, CurConComp, N, x + 1, y, RegionVal);
    if ((y < N - 1 and not Visited[y + 1][x]) and Board[y + 1][x] == RegionVal) Count += SingleCowFloodFill(Board, Visited, CurConComp, N, x, y + 1, RegionVal);
    return Count;
}

int SingleCow(vector<vector<int> >& Board, vector<simps>& NewRegions, int& RegionCount, const int N) {
    int CurConComp = 0, Best = 0;
    vector<vector<bool> > Visited;
    for (int y = 0; y < N; y++) {
        vector<bool> Row(N);
        Visited.push_back(Row);
    }
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (not Visited[y][x]) {
                NewRegions.push_back({Board[y][x], 0});
                int CurRegion = SingleCowFloodFill(Board, Visited, CurConComp, N, x, y, Board[y][x]);
                NewRegions.back().second = CurRegion;
                Best = max(CurRegion, Best);
                CurConComp++;
            }
        }
    }
    RegionCount = CurConComp;
    return Best;
}

int DoubleCowBfs(vector<unordered_set<int> >& Connections, const vector<simps>& NewRegions, const int a, const int b, const int Start) {
    int Count = 0;
    queue<int> BfsQueue;
    unordered_set<int> Visited;
    BfsQueue.push(Start);
    while (BfsQueue.size() > 0) {
        int Cur = BfsQueue.front();
        vector<int> ToRemove;
        Visited.insert(Cur);
        BfsQueue.pop();
        for (int i : Connections[Cur]) {
            if (NewRegions[i].first == a or NewRegions[i].first == b) {
                BfsQueue.push(i);
                ToRemove.push_back(i);
            }
        }
        for (int i : ToRemove) {
            Connections[i].erase(Cur);
            Connections[Cur].erase(i);
        }
    }
    for (int i : Visited) Count += NewRegions[i].second;
    return Count;
}

int DoubleCow(const vector<vector<int> >& Board, const vector<simps>& NewRegions, const int RegionCount, const int N) {
    int Best = 0;
    vector<unordered_set<int> > Connections(RegionCount);
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (x < N - 1) {
                int a = Board[y][x], b = Board[y][x + 1];
                if (a != b) {
                    Connections[a].insert(b);
                    Connections[b].insert(a);
                }
            }
            if (y < N - 1) {
                int a = Board[y][x], b = Board[y + 1][x];
                if (a != b) {
                    Connections[a].insert(b);
                    Connections[b].insert(a);
                }
            }
        }
    }
    for (int i = 0; i < RegionCount; i++) {
        while (Connections[i].size() > 0) Best = max(DoubleCowBfs(Connections, NewRegions, NewRegions[i].first, NewRegions[*Connections[i].begin()].first, i), Best);
    }
    return Best;
}

int main() {
    int N, RegionCount;
    vector<simps> NewRegions;
    vector<vector<int> > Board;
    fin >> N;
    for (int y = 0; y < N; y++) {
        vector<int> Row(N);
        for (int x = 0; x < N; x++) fin >> Row[x];
        Board.push_back(Row);
    }
    fout << SingleCow(Board, NewRegions, RegionCount, N) << "\n" << DoubleCow(Board, NewRegions, RegionCount, N) << "\n";
    return 0;
}
