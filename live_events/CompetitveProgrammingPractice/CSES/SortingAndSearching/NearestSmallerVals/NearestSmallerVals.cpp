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
vector<simps> stck;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int cur;
        cin >> cur;
        while (not stck.empty() and cur <= stck.back().first) stck.pop_back();
        cout << (stck.empty() ? 0 : stck.back().second) << " ";
        stck.push_back({cur, i});
    }
    cout << "\n";
	return 0;
}
