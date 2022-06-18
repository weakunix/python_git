#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void Dfs(const vector<vector<int> >& Graph, vector<bool>& Visited, unordered_set<int>& TarSet, const int Cur) {
    TarSet.insert(Cur);
    Visited[Cur] = true;
    for (int i : Graph[Cur]) {
        if (not Visited[i]) Dfs(Graph, Visited, TarSet, i);
    }
    return;
}

int main() {
    int N;
    cin >> N;
    vector<vector<int> > Graph(N), ReverseGraph(N);
    for (int i = 0; i < N; i++) {
        bool MorePreferedPresent = true;
        for (int j = 0; j < N; j++) {
            int a;
            cin >> a;
            a--;
            if (MorePreferedPresent) {
                Graph[i].push_back(a);
                ReverseGraph[a].push_back(i);
                if (a == i) MorePreferedPresent = false;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        vector<bool> Visited(N);
        unordered_set<int> ConnectedToCur;
        Dfs(ReverseGraph, Visited, ConnectedToCur, i);
        for (int j : Graph[i]) {
            if (ConnectedToCur.count(j) > 0) {
                cout << j + 1 << "\n";
                break;
            }
        }
    }
    return 0;
}
