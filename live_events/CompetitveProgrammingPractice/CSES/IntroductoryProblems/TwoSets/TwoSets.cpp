#include <iostream>
#include <vector>
#include <utility>
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

ll n, cur;
vector<int> t, f;
vector<bool> used;

int main() {
    cin >> n;
    used.resize(n + 1);
    if (n % 4 != 0 and (n + 1) % 4 != 0) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    cur = n * (n + 1) / 4;
    for (int i = n; i < cur; i--) {
        used[i] = true;
        cur -= i;
    }
    used[cur] = true;
    for (int i = 1; i <= n; i++) {
        if (used[i]) t.push_back(i);
        else f.push_back(i);
    }
    cout << t.size() << "\n";
    for (int i : t) cout << i << " ";
    cout << "\n";
    cout << f.size() << "\n";
    for (int i : f) cout << i << " ";
    cout << "\n";
	return 0;
}
