#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

const int ModVal = 1e9 + 7;
int N, M, X, Y, K;
vector<int> Comps;
vector<vector<simps> > Adj;
vector<map<ll, ll> > CompLens;

void Dfs(const int Node, const int Parent, const int CurComp, const ll Dist, bool IsFirst = false) {
    assert(CurComp >= 0 and CurComp < K);
    assert(Node >= 0 and Node < N);
    Comps[Node] = CurComp;
    if (Dist > 0 or not IsFirst) CompLens[CurComp][Dist + X]++;
    for (const simps& s : Adj[Node]) {
        if (s.first != Parent) Dfs(s.first, Node, CurComp, Dist + s.second);
    }
    return;
}

void SetCompLens() {
    int CurComp = 0;
    for (int i = 0; i < N; i++) {
        if (Comps[i] == -1) {
            Dfs(i, -1, CurComp, 0, true);
            CurComp++;
        }
        else Dfs(i, -1, Comps[i], 0, true);
    }
    return;
}

ll GetAns(ll Ans) {
    for (int i = 1; i < K; i++) {
        Ans = (Ans * i) % ModVal;
        Ans = (Ans * 2) % ModVal;
    }
    return Ans;
}

int main() {
    //freopen("2.in", "r", stdin);
    freopen("mooriokart.in", "r", stdin);
    freopen("mooriokart.out", "w", stdout);

    cin >> N >> M >> X >> Y;
    K = N - M;
    vector<vector<ll> > DpSum(K), DpCount(K);
    Comps.resize(N, -1);
    Adj.resize(N);
    CompLens.resize(K);
    for (int i = 0; i < K; i++) {
        DpSum[i].resize(Y + 1);
        DpCount[i].resize(Y + 1);
    }
    for (int i = 0; i < M; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a--;
        b--;
        Adj[a].push_back({b, d});
        Adj[b].push_back({a, d});
    }

    SetCompLens();

    for (const auto it : CompLens[0]) {
        assert(it.first > 0);
        assert(it.second % 2 == 0);
        ll val = it.first, count = it.second / 2, sum = (val * count) % ModVal;
        if (val < Y) {
            DpSum[0][val] = (DpSum[0][val] + sum) % ModVal;
            DpCount[0][val] = (DpCount[0][val] + count) % ModVal;
        }
        else {
            DpSum[0][Y] = (DpSum[0][Y] + sum) % ModVal;
            DpCount[0][Y] = (DpCount[0][Y] + count) % ModVal;
        }
    }
    for (int i = 0; i < K - 1; i++) {
        for (int j = 0; j < Y; j++) {
            ll a = DpCount[i][j], b = DpSum[i][j];
            for (const auto it : CompLens[i + 1]) {
                assert(it.first > 0);
                assert(it.second % 2 == 0);
                ll val = it.first, count = it.second / 2, sum = (val * count) % ModVal;
                if (val + j < Y) {
                    DpSum[i + 1][val + j] = (DpSum[i + 1][val + j] + ((a * sum) % ModVal) + ((b * count) % ModVal)) % ModVal;
                    DpCount[i + 1][val + j] = (DpCount[i + 1][val + j] + ((a * count) % ModVal)) % ModVal;
                }
                else {
                    DpSum[i + 1][Y] = (DpSum[i + 1][Y] + ((a * sum) % ModVal) + ((b * count) % ModVal)) % ModVal;
                    DpCount[i + 1][Y] = (DpCount[i + 1][Y] + ((a * count) % ModVal)) % ModVal;
                }
            }
        }
        ll a = DpCount[i][Y], b = DpSum[i][Y];
        for (const auto it : CompLens[i + 1]) {
            assert(it.first > 0);
            assert(it.second % 2 == 0);
            ll val = it.first, count = it.second / 2, sum = (val * count) % ModVal;
            DpSum[i + 1][Y] = (DpSum[i + 1][Y] + ((a * sum) % ModVal) + ((b * count) % ModVal)) % ModVal;
            DpCount[i + 1][Y] = (DpCount[i + 1][Y] + ((a * count) % ModVal)) % ModVal;
        }
    }

    cout << GetAns(DpSum[K - 1][Y]) << "\n";

    return 0;
}
