#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

int n, curht = 0, arr[N], ans = -1, idxans = -1;
vector<int> seeable;

int getcnt(int h, int st, int en) {
    int res = 0;
    for (int i = st; i <= en; i++) {
        res += (arr[i] > h);
        h = max(arr[i], h);
    }
    return res;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] > curht) {
            seeable.push_back(i);
            curht = arr[i];
        }
    }

    if (getcnt(0, 0, n - 1) == n) {
        cout << "1\n";
        return 0;
    }

    for (int i = 0; i < seeable.size(); i++) {
        int cur = getcnt(i == 0 ? 0 : arr[seeable[i - 1]], seeable[i] + 1, i == seeable.size() - 1 ? n - 1 : seeable[i + 1] - 1);
        if (cur > ans) {
            idxans = seeable[i] + 1;
            ans = cur;
        }
    }

    if (ans == 0) {
        set<int> s;
        for (int i : seeable) s.insert(i);
        for (int i = 0; i < n; i++) {
            if (s.count(i) == 0) {
                cout << i + 1 << "\n";
                return 0;
            }
        }
        assert(false);
    }

    cout << idxans << "\n";

	return 0;
}
