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

int n;
vector<bool> seen;

int main() {
    cin >> n;
    seen.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int cur;
        cin >> cur;
        seen[cur - 1] = true;
    }
    for (int i = 0; i < n; i++) {
        if (not seen[i]) cout << i + 1 << "\n";
    }
	return 0;
}
