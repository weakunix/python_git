#include <iostream>
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

int n, q;
vector<int> pfx;

int main() {
    cin >> n >> q;
    pfx.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> pfx[i];
        pfx[i] ^= pfx[i - 1];
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        cout << (pfx[b] ^ pfx[a - 1]) << "\n";
    }
	return 0;
}
