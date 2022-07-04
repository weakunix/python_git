#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

ofstream fout("truth.out");
ifstream fin("truth.in");

bool Bfs(const vector<vector<simps> >& Graph, vector<int>& Visited, const int StartingNode) {
    queue<int> NodeQueue;
    Visited[StartingNode] = 1;
    NodeQueue.push(StartingNode);
    while (NodeQueue.size() > 0) {
        for (const simps& s : Graph[NodeQueue.front()]) {
            if (Visited[s.first] == 0) {
                if (s.second == 1) Visited[s.first] = Visited[NodeQueue.front()];
                else Visited[s.first] = Visited[NodeQueue.front()] * -1;
                NodeQueue.push(s.first);
            }
            else {
                if (s.second == 1 and Visited[s.first] != Visited[NodeQueue.front()]) return false;
                else if (s.second == -1 and Visited[s.first] == Visited[NodeQueue.front()]) return false;
            }
        }
        NodeQueue.pop();
    }
    return true;
}

int main() {
    int N, M, Ans = 0;
    fin >> N >> M;
    vector<vector<simps> > Graph(N);
    for (int i = 0; i < M; i++) {
        int x, y;
        char Claim;
        bool Done = false;
        vector<int> Visited(N);
        fin >> x >> y >> Claim;
        x--;
        y--;
        if (Claim == 'T') {
            Graph[x].push_back({y, 1});
            Graph[y].push_back({x, 1});
        }
        else {
            Graph[x].push_back({y, -1});
            Graph[y].push_back({x, -1});
        }
        for (int i = 0; i < N; i++) {
            if (Visited[i] == 0) {
                if (not Bfs(Graph, Visited, i)) {
                    Done = true;
                    break;
                }
            }
        }
        if (Done) break;
        Ans++;
    }
    fout << Ans << "\n";
    return 0;
}
