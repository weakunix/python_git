#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()

vector<int> Parent, StartRoots;

int GetRoot(const int Node) {
    if (Parent[Node] < 0) return Node;
    Parent[Node] = GetRoot(Parent[Node]);
    return Parent[Node];
}

int Merge(int a, int b) {
    if (a < b) swap(a, b);
    Parent[b] += Parent[a];
    Parent[a] = b;
    StartRoots[b] += StartRoots[a];
    StartRoots[a] = 0;
    return -Parent[b];
}

int main() {
    freopen("skilevel.in", "r", stdin);
    freopen("skilevel.out", "w", stdout);

    int M, N, T, StartLeft = 0;
    ll Ans = 0;
    vector<int> Nodes;
    vector<threesome> Edges;
    cin >> M >> N >> T;
    Parent.resize(M * N, -1);
    StartRoots.resize(M * N);
    for (int i = 0; i < M * N; i++) {
        int Cur;
        cin >> Cur;
        Nodes.push_back(Cur);
        if (i % N > 0) Edges.push_back({abs(Cur - Nodes[i - 1]), {i, i - 1}});
        if (i >= N) Edges.push_back({abs(Cur - Nodes[i - N]), {i, i - N}});
    }
    for (int i = 0; i < M * N; i++) {
        int Cur;
        cin >> Cur;
        if (Cur) {
            StartLeft++;
            StartRoots[i]++;
        }
    }
    sort(all(Edges));

    if (T == 1) {
        cout << "0\n";
        return 0;
    }
    for (const threesome& t : Edges) {
        int D = t.first, a = t.sec, b = t.third;
        if (GetRoot(a) != GetRoot(b)) {
            if (Merge(GetRoot(a), GetRoot(b)) >= T) {
                Ans += (ll) StartRoots[GetRoot(a)] * D;
                StartLeft -= StartRoots[GetRoot(a)];
                StartRoots[GetRoot(a)] = 0;
                if (StartLeft == 0) {
                    cout << Ans << "\n";
                    return 0;
                }
            }
        }
    }
    return 1;
}
