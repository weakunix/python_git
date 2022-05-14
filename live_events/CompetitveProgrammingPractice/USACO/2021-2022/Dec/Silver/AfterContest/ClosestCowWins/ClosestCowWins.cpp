#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define rall(v) v.rbegin(), v.rend()

ll GetBestCow(const vector<simps>& Considered, int Start, int End) {
    int Range = (End - Start) / 2;
    assert(Range > 0);
    ll Cur = 0, Best = 0;
    queue<simps> InRange;
    for (const simps& s : Considered) {
        InRange.push(s);
        Cur += s.second;
        while (s.first - InRange.front().first >= Range) {
            Cur -= InRange.front().second;
            InRange.pop();
        }
        assert(s.first - InRange.front().first >= 0);
        Best = max(Cur, Best);
    }
    return Best;
}

int main() {
    int K, M, N, Prev = -1, Count = 0;
    ll Ans = 0;
    cin >> K >> M >> N;
    vector<ll> Nhoj(M), BestCows;
    vector<simps> Grass(K);
    for (int i = 0; i < K; i++) cin >> Grass[i].first >> Grass[i].second;
    sort(rall(Grass));
    for (int i = 0; i < M; i++) cin >> Nhoj[i];
    sort(rall(Nhoj));
    while (Nhoj.size() > 0) {
        int Cur = Nhoj.back();
        vector<simps> Considered;
        Nhoj.pop_back();
        while (Grass.size() > 0 and Grass.back().first < Cur) {
            assert(Grass.back().first > Prev);
            Considered.push_back(Grass.back());
            Grass.pop_back();
        }
        if (Considered.size() > 0) {
            if (Prev == -1) {
                ll CurBestCow = 0;
                for (const simps& s : Considered) CurBestCow += s.second;
                BestCows.push_back(CurBestCow);
            }
            else {
                ll CurBestCow = GetBestCow(Considered, Prev, Cur);
                ll TwoCows = 0;
                for (const simps& s : Considered) TwoCows += s.second;
                BestCows.push_back(CurBestCow);
                BestCows.push_back(TwoCows - CurBestCow);
            }
        }
        Prev = Cur;
    }
    BestCows.push_back(0);
    auto it = BestCows.end();
    it--;
    for (const simps& s : Grass) *it += s.second;
    sort(rall(BestCows));
    for (ll i : BestCows) {
        if (Count == N) break;
        Ans += i;
        Count++;
    }
    cout << Ans << "\n";
    return 0;
}
