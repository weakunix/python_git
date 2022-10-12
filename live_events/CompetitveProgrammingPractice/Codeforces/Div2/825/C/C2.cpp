#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

int main() {
    int n;
    ll og = 0;
    cin >> n;
    vector<int> a(n), stuck(n), gotstuck(n, -1);
    for (int i = 0; i < n; i++) cin >> a[i];

    int r = 0;
    for (int l = 0; l < n; l++) {
        while (r < n and a[r] >= r - l + 1) r++;
        stuck[l] = r;
        if (gotstuck[r] == -1) gotstuck[r] = l;
        og += r - l;
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int idx, newval;
        cin >> idx >> newval;
        if (a[idx - 1] == newval) {
            cout << og << "\n";
            continue;
        }
        if (a[idx - 1] < newval) {
            if (gotstuck[idx - 1] == -1) {
                cout << og << "\n";
                continue;
            }
            auto it = upper_bound(all(stuck), idx - 1);
            int unstuck = it - stuck.begin();
            cout << og + (unstuck - gotstuck[idx - 1]) * (*it - (idx - 1)) << "\n";
        }
        upper_bound(all(stuck), idx - 1) - stuck.begin();
        idx - newval
    }   

	return 0;
}
