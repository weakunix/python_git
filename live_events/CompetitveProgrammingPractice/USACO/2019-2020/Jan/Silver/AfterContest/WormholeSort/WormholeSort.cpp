#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define rall(v) v.rbegin(), v.rend()

ofstream fout("wormsort.out");
ifstream fin("wormsort.in");

void Dfs(const vector<vector<int> >& Connections, vector<bool>& Visited, unordered_map<int, int>& ConnectedComponentGroups, int Group, int Cow) {
    Visited[Cow] = true;
    ConnectedComponentGroups[Cow] = Group;
    for (int i : Connections[Cow]) {
        if (not Visited[i]) Dfs(Connections, Visited, ConnectedComponentGroups, Group, i);
    }
    return;
}

bool IsPossibleMinWidth(const vector<threesome>& Wormholes, const unordered_map<int, int>& Cows, int N, int Width) {
    int Count = 0;
    vector<bool> Visited(N);
    vector<vector<int> > Connections(N);
    unordered_map<int, int> ConnectedComponentGroups;
    for (const threesome& t : Wormholes) {
        if (t.first >= Width) {
            Connections[t.sec].push_back(t.third);
            Connections[t.third].push_back(t.sec);
        }
        else break;
    }
    for (int i = 0; i < N; i++) {
        if (not Visited[i]) {
            Count++;
            Dfs(Connections, Visited, ConnectedComponentGroups, Count, i);
        }
    }
    for (int i = 0; i < N; i++) {
        if (ConnectedComponentGroups[i] != ConnectedComponentGroups[Cows.at(i)]) return false;
    }
    return true;
}

int main() {
    int N, M, Low = 1, High = 1e9 + 1;
    vector<threesome> Wormholes;
    unordered_map<int, int> Cows;
    fin >> N >> M;
    for (int i = 0; i < N; i++) {
        int Cow;
        fin >> Cow;
        Cow--;
        Cows[i] = Cow;
    }
    for (int i = 0; i < M; i++) {
        int a, b, w;
        fin >> a >> b >> w;
        a--;
        b--;
        Wormholes.push_back({w, {a, b}});
    }
    sort(rall(Wormholes));
    while (Low < High) {
        int Mid = Low + (High - Low + 1) / 2;
        if (IsPossibleMinWidth(Wormholes, Cows, N, Mid)) Low = Mid;
        else High = Mid - 1;
    }
    assert(Low == High);
    if (Low == 1e9 + 1) fout << "-1\n";
    else fout << Low << "\n";
    return 0;
}
