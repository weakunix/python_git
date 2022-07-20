#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define all(v) v.begin(), v.end()

bool SortAcorns(const pii& a, const pii& b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first > b.first;
}

ll RaisePow(const int Acorn, const int ModVal, const int Exponent) {
    ll Ans = 1;
    for (int i = 0; i < Exponent; i++) {
        Ans *= Acorn;
        Ans %= ModVal;
    }
    return Ans;
}

pii GenAcorn(const int a, const int b, const int c, const int d, const int e, const int f, const int g, const int h, const int Acorn) {
    ll Weight = (((a * RaisePow(Acorn, d, 5)) % d) + (b * RaisePow(Acorn, d, 2)) % d + c % d) % d, Utility = (((e * RaisePow(Acorn, h, 5)) % h) + (f * RaisePow(Acorn, h, 3)) % h + g % h) % h;
    return {Utility, Weight};
    
}

int main() {
    int N, a, b, c, d, e, f, g, h, M;
    ll TotalWeight = 0;
    vector<pii> Acorns;
    cin >> N >> a >> b >> c >> d >> e >> f >> g >> h >> M;
    for (int i = 0; i < 3 * N; i++) Acorns.push_back(GenAcorn(a, b, c, d, e, f, g, h, i));
    sort(all(Acorns), SortAcorns);
    for (int i = 0; i < N; i++) {
        TotalWeight += Acorns[i].second;
        TotalWeight %= M;
    }
    cout << TotalWeight << "\n";
    return 0;
}
