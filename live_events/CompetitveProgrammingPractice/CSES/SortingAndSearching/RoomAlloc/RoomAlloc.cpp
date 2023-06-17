#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 2e5;

int n, k = 0, prv = -1, ans[N], times[2 * N];
vector<int> avail;
unordered_map<int, vector<int>> arrive, leave;

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        times[2 * i] = a;
        times[2 * i + 1] = b;
        arrive[a].push_back(i);
        leave[b].push_back(i);
    }
    sort(times, times + 2 * n);
    for (int i : times) {
        if (i == prv) continue;
        prv = i;
        for (int j : arrive[i]) {
            if (avail.empty()) {
                k++;
                avail.push_back(k);
            }
            ans[j] = avail.back();
            avail.pop_back();
        }
        for (int j : leave[i]) avail.push_back(ans[j]);
    }
    cout << k << "\n";
    for (int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";
	return 0;
}
