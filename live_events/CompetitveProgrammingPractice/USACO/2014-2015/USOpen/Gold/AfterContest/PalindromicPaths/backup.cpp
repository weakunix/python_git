#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 500, modval = 1e9 + 7, topx[4] = {-1, 0, -1, 0}, topy[4] = {0, -1, 0, -1}, botx[4] = {1, 1, 0, 0}, boty[4] = {0, 0, 1, 1};

int n;
string arr[N];
map<ll, ll> prv;

int comp(int x, int y) {
    return x + y * n;
}

int getx(int compressed) {
    return compressed % n;
}

int gety(int compressed) {
    return compressed / n;
}

ll fullcomp(int comp1, int comp2) {
    return comp1 + (ll) n * n * comp2;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];

    for (int i = 0; i < n; i++) prv[fullcomp(comp(i, n - i - 1), comp(i, n - i - 1))] = 1;

    for (int i = 0; i < n - 1; i++) {
        map<ll, ll> cur;
        for (auto& u : prv) {
            int fi = u.first % (n * n), se = u.first / (n * n);
            for (int j = 0; j < 4; j++) {
                int tx = getx(fi) + topx[j], ty = gety(fi) + topy[j], bx = getx(se) + botx[j], by = gety(se) + boty[j];
                if ((tx < 0 or ty < 0) or (bx >= n or by >= n)) continue;
                if (arr[ty][tx] == arr[by][bx]) cur[fullcomp(comp(tx, ty), comp(bx, by))] = (cur[fullcomp(comp(tx, ty), comp(bx, by))] + u.second) % modval;
            }
        }
        swap(cur, prv);
    }

    cout << prv[fullcomp(comp(0, 0), comp(n - 1, n - 1))] << "\n";
	return 0;
}
