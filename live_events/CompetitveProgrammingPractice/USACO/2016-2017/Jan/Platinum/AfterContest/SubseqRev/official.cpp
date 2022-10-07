#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

int n;
vector<int> a;
vector<vector<vector<vector<int>>>> dp;

int getdp(int start, int end, int small, int big) {
    int left = a[start], right = a[end];
    int& cur = dp[start][end][small][big];
    if (cur != -1) return cur;

    cur = 0;
    if (start == end) {
        assert(left == right);
        if (left >= small and left <= big) cur = 1;
        return cur;
    }
    if (start + 1 == end) {
        if (left > right) swap(left, right);
        if (left >= small and left <= big) cur = 1;
        if (right >= small and right <= big) cur = 1;
        if (left >= small and right <= big) cur = 2;
        return cur;
    }

    cur = max(getdp(start + 1, end - 1, small, big), cur);
    if (left >= small and left <= big) cur = max(getdp(start + 1, end, left, big) + 1, cur);
    if (right >= small and right <= big) cur = max(getdp(start, end - 1, small, right) + 1, cur);
    if ((left >= small and right <= big) and left <= right) cur = max(getdp(start + 1, end - 1, left, right) + 2, cur);
    
    cur = max(getdp(start + 1, end, small, big), cur);
    cur = max(getdp(start, end - 1, small, big), cur);

    swap(left, right);
    if (left >= small and left <= big) cur = max(getdp(start + 1, end - 1, left, big) + 1, cur);
    if (right >= small and right <= big) cur = max(getdp(start + 1, end - 1, small, right) + 1, cur);
    if ((left >= small and right <= big) and left <= right) cur = max(getdp(start + 1, end - 1, left, right) + 2, cur);

    return cur;
}

int main() {
    freopen("subrev.in", "r", stdin);
    freopen("subrev.out", "w", stdout);

    cin >> n;
    a.resize(n);
    dp.resize(n, vector<vector<vector<int>>>(n, vector<vector<int>>(50, vector<int>(50, -1))));
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    cout << getdp(0, n - 1, 0, 49) << "\n";

	return 0;
}
