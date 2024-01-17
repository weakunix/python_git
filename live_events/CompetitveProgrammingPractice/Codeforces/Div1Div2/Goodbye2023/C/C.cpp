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

const int N = 1e5 + 1;

int t, odd[N];

void subcase() {
    int n, cnt = 0;
    ll sm = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        cnt += cur % 2;
        sm += cur;
        if (i == 0) cout << cur << " ";
        else cout << sm - odd[cnt] << " ";
    }
    cout << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    odd[0] = 0;
    odd[1] = 1;
    odd[2] = 0;
    for (int i = 3; i < N; i++) odd[i] = odd[i - 3] + 1;

	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
