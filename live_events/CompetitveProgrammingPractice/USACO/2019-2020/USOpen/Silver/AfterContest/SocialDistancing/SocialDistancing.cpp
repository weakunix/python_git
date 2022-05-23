#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;

#define all(v) v.begin(), v.end()

ofstream fout("socdist.out");
ifstream fin("socdist.in");

bool CanSocDist(const vector<simps>& Grass, ll D, int N) {
    ll CurLoc = Grass[0].first - D;
    auto it = Grass.begin();
    for (int i = 0; i < N; i++) {
        CurLoc += D;
        while (it != Grass.end() and it->second < CurLoc) it++;
        if (it == Grass.end()) return false;
        if (CurLoc < it->first) CurLoc = it->first;
    }
    return true;
}

int main() {
    int N, M;
    ll Low = 1, High = 1e18, Ans = 0;
    fin >> N >> M;
    vector<simps> Grass(M);
    for (int i = 0; i < M; i++) fin >> Grass[i].first >> Grass[i].second;
    sort(all(Grass));
    while (Low <= High) {
        ll Mid = Low + (High - Low + 1) / 2;
        if (CanSocDist(Grass, Mid, N)) {
            Ans = Mid;
            Low = Mid + 1;
        }
        else High = Mid - 1;
    }
    assert(Ans > 0);
    fout << Ans << "\n";
    return 0;
}
