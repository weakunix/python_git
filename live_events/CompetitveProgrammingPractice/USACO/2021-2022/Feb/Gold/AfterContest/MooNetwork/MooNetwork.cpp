#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<ll, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()

int N, EdgeCount = 0;
ll Ans = 0;
vector<int> YStarts(11), Parent;
vector<vector<ll> > CowLocs(11);
vector<threesome> Edges;

ll GetSquare(const ll n) {
    return n * n;
}

int GetRoot(const int Node) {
    if (Parent[Node] < 0) return Node;
    Parent[Node] = GetRoot(Parent[Node]);
    return Parent[Node];
}

bool Merge(int a, int b) {
    a = GetRoot(a);
    b = GetRoot(b);
    if (a == b) return false;
    if (Parent[a] < Parent[b]) swap(a, b);
    Parent[b] += Parent[a];
    Parent[a] = b;
    return true;
}

int main() {
    //freopen("test.in", "r", stdin);

    cin >> N;
    Parent.resize(N, -1);
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        CowLocs[y].push_back(x);
    }

    for (int i = 0; i < 11; i++) {
        sort(all(CowLocs[i]));
        if (i == 0) YStarts[i] = 0;
        else YStarts[i] = YStarts[i - 1] + CowLocs[i - 1].size();
    }

    for (int y1 = 0; y1 < 11; y1++) {
        if (CowLocs[y1].size() == 0) continue;
        for (int i = 0; i < CowLocs[y1].size() - 1; i++) Edges.push_back({GetSquare((CowLocs[y1][i + 1] - CowLocs[y1][i])), {YStarts[y1] + i, YStarts[y1] + i + 1}});
        for (int y2 = y1 + 1; y2 < 11; y2++) {
            if (CowLocs[y2].size() == 0) continue;
            int First = 0, Second = 0;
            while (First < CowLocs[y1].size() and Second < CowLocs[y2].size()) {
                Edges.push_back({GetSquare(CowLocs[y1][First] - CowLocs[y2][Second]) + GetSquare(y2 - y1), {YStarts[y1] + First, YStarts[y2] + Second}});
                if (First == CowLocs[y1].size() - 1) Second++;
                else if (Second == CowLocs[y2].size() - 1) First++;
                else {
                    if (CowLocs[y1][First] < CowLocs[y2][Second]) First++;
                    else Second++;
                }
            }
        }
    }

    sort(all(Edges));

    for (const threesome& t : Edges) {
        if (Merge(t.sec, t.third)) {
            Ans += t.first;
            EdgeCount++;
            if (EdgeCount == N - 1) break;
        }
    }

    cout << Ans << "\n";

    return 0;
}
