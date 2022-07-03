#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

ll IndegreeZero(const vector<int>& Visits, vector<int>& Indegree, const vector<int>& Moos, vector<bool>& Visited, const int N) {
    ll Ans = 0;
    queue<int> ZeroIndegreeNodes;
    for (int i = 0; i < N; i++) {
        if (Indegree[i] == 0) ZeroIndegreeNodes.push(i);
    }
    while (ZeroIndegreeNodes.size() > 0) {
        int Node = ZeroIndegreeNodes.front();
        Visited[Node] = true;
        Ans += Moos[Node];
        Indegree[Visits[Node]]--;
        if (Indegree[Visits[Node]] == 0) ZeroIndegreeNodes.push(Visits[Node]);
        ZeroIndegreeNodes.pop();
    }
    return Ans;
}

ll Cycle(const vector<int>& Visits, const vector<int>& Moos, vector<bool>& Visited, int Node) {
    int Best = 1e9;
    ll Total = 0;
    while (not Visited[Node]) {
        Visited[Node] = true;
        Total += Moos[Node];
        Best = min(Moos[Node], Best);
        Node = Visits[Node];
    }
    return Total - Best;
}

int main() {
    int N;
    ll Ans = 0;
    cin >> N;
    vector<int> Visits, Indegree(N), Moos;
    vector<bool> Visited(N);
    for (int i = 0; i < N; i++) {
        int a, v;
        cin >> a >> v;
        a--;
        Visits.push_back(a);
        Indegree[a]++;
        Moos.push_back(v);
    }
    Ans += IndegreeZero(Visits, Indegree, Moos, Visited, N);
    for (int i = 0; i < N; i++) {
        if (not Visited[i]) Ans += Cycle(Visits, Moos, Visited, i);
    }
    cout << Ans << "\n";
    return 0;
}
