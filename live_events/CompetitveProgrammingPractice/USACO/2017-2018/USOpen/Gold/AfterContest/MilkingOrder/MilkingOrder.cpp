#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

int N, M;
vector<vector<int> > Obs;

vector<int> TestX(const int X) {
    vector<int> Indegree(N), Toposort;
    vector<vector<int> > Graph(N);
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Obs[i].size() - 1; j++) {
            Indegree[Obs[i][j + 1]]++;
            Graph[Obs[i][j]].push_back(Obs[i][j + 1]);
        }
    }

    priority_queue<int> NodePq;
    for (int i = 0; i < N; i++) {
        if (Indegree[i] == 0) NodePq.push(-i);
    }

    while (not NodePq.empty()) {
        int Node = -NodePq.top();
        NodePq.pop();
        Toposort.push_back(Node);
        for (int i : Graph[Node]) {
            Indegree[i]--;
            assert(Indegree[i] >= 0);
            if (Indegree[i] == 0) NodePq.push(-i);
        }
    }

    return Toposort;
}

int main() {
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);

    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int m;
        cin >> m;
        Obs.push_back({});
        for (int j = 0; j < m; j++) {
            int cur;
            cin >> cur;
            cur--;
            Obs[i].push_back(cur);
        }
    }

    int Low = 0, High = M;
    while (Low < High) {
        int Mid = Low + (High - Low + 1) / 2;
        if (TestX(Mid).size() == N) Low = Mid;
        else High = Mid - 1;
    }
    
    assert(Low == High);
    assert(Low > 0);

    vector<int> Ans = TestX(Low);
    assert(Ans.size() == N);
    for (int i = 0; i < N; i++) {
        cout << Ans[i] + 1;
        if (i < N - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}
