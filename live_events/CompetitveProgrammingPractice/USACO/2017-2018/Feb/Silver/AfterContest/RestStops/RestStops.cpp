#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define rall(v) v.rbegin(), v.rend()

ofstream fout("reststops.out");
ifstream fin("reststops.in");

int main() {
    int L, N, Fj, Bessie, CurLoc = 0;
    ll Ans = 0;
    fin >> L >> N >> Fj >> Bessie;
    vector<simps> RestStops(N);
    for (int i = 0; i < N; i++) fin >> RestStops[i].second >> RestStops[i].first;
    sort(rall(RestStops));
    for (const simps& s : RestStops) {
        if (s.second > CurLoc) {
            ll FjTime = (ll) Fj * (s.second - CurLoc), BessieTime = (ll) Bessie * (s.second - CurLoc);
            Ans += (FjTime - BessieTime) * s.first;
            CurLoc = s.second;
        }
    }
    fout << Ans << "\n";
    return 0;
}
