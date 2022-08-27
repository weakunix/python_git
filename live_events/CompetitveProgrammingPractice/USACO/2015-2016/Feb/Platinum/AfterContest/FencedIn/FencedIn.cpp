#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, bool> simps;

#define all(v) v.begin(), v.end()

int A, B, n, m, Col = 0, Row = 0;
ll Ans = 0;
vector<int> Vert, Horz;
vector<simps> Fences;

int main() {
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    cin >> A >> B >> n >> m;
    Vert.resize(n);
    Horz.resize(m);
    for (int i = 0; i < n; i++) cin >> Vert[i];
    for (int i = 0; i < m; i++) cin >> Horz[i];
    Vert.push_back(0);
    Vert.push_back(A);
    Horz.push_back(0);
    Horz.push_back(B);

    sort(all(Vert));
    sort(all(Horz));

    for (int i = 0; i <= n; i++) Fences.push_back({Vert[i + 1] - Vert[i], true});
    for (int i = 0; i <= m; i++) Fences.push_back({Horz[i + 1] - Horz[i], false});

    sort(all(Fences));

    for (const simps& s : Fences) {
        if (s.second) {
            if (Col == 0) Ans += m * s.first;
            else Ans += min(m + 1 - Row, m) * s.first;
            Col++;
        }
        else {
            if (Row == 0) Ans += n * s.first;
            else Ans += min(n + 1 - Col, n) * s.first;
            Row++;
        }
    }

    cout << Ans << "\n";

    return 0;
}
