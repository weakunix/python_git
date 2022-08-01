#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

vector<int> Parent;

int GetRoot(const int Node) {
    if (Parent[Node] < 0) return Node;
    Parent[Node] = GetRoot(Parent[Node]);
    return Parent[Node];
}

void Merge(int a, int b) {
    if (Parent[a] < Parent[b]) swap(a, b);
    Parent[b] += Parent[a];
    Parent[a] = b;
    return;
}

int main() {
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);

    int N, Q;
    vector<threesome> Edges, Queries;
    cin >> N >> Q;
    vector<int> Ans(Q);
    Parent.resize(N, -1);
    for (int i = 0; i < N - 1; i++) {
        int a, b, r;
        cin >> a >> b >> r;
        a--;
        b--;
        Edges.push_back({r, {a, b}});
    }
    for (int i = 0; i < Q; i++) {
        int k, v;
        cin >> k >> v;
        v--;
        Queries.push_back({k, {v, i}});
    }
    sort(all(Edges));
    sort(rall(Queries));
    for (const threesome& t : Queries) {
        int k = t.first, v = t.sec, i = t.third;
        while (Edges.size() > 0 and Edges.back().first >= k) {
            Merge(GetRoot(Edges.back().sec), GetRoot(Edges.back().third));
            Edges.pop_back();
        }
        Ans[i] = -Parent[GetRoot(v)] - 1;
    }
    for (int i : Ans) cout << i << "\n";
    return 0;
}
