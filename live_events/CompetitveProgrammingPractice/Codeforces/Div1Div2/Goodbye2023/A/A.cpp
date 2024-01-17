#include <iostream>
#include <string>
#include <cstring>
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

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

int t;

void subcase() {
    int n, k, val = 2023;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        if (val == -1) continue;
        if (val % cur) val = -1;
        else val /= cur;
    }
    if (val == -1) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n" << val << " ";
    for (int i = 1; i < k; i++) cout << "1 ";
    cout << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
