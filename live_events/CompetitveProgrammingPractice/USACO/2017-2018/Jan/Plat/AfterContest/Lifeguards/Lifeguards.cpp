#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
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

const int N = 1e5, K = 101;

int n, k, leftmost[N], dp1[N][K], dp2[N][K];
simps arr[N];
vector<int> valid;

void genvalid() {
    int r = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i].second > r) {
            valid.push_back(i);
            r = arr[i].second;
        }
        else k--;
    }
    n = valid.size();
    k = max(0, k);
    return;
}

void genleftmost() {
    queue<int> q;
    for (int i = 0; i < n; i++) {
        int cur = valid[i];
        while (q.size() and arr[valid[q.front()]].second <= arr[cur].first) q.pop();
        if (q.empty()) leftmost[i] = -1;
        else leftmost[i] = q.front();
        q.push(i);
    }
    return;
}

int main() {
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            dp1[i][j] = -2e9;
            dp2[i][j] = -2e9;
        }
    }

    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> arr[i].first >> arr[i].second;
    sort(arr, arr + n);
    genvalid();
    genleftmost();
    

    dp1[0][0] = arr[valid[0]].second - arr[valid[0]].first;
    dp2[0][0] = 0;
    dp2[0][1] = 0;

    for (int i = 1; i < n; i++) {
        int cur = valid[i];

        dp1[i][min(i, k)] = arr[cur].second - arr[cur].first;
        dp2[i][min(i + 1, k)] = 0;

        for (int j = 0; j <= k; j++) {
            if (leftmost[i] != -1) {
                int rem = max(j - (i - leftmost[i] - 1), 0);
                dp1[i][j] = max({dp1[leftmost[i]][rem] + arr[cur].second - arr[valid[leftmost[i]]].second, dp2[leftmost[i]][rem] + arr[cur].second - arr[cur].first, dp1[i][j]});
            }
            else dp1[i][j] = max({dp1[i - 1][j] + arr[cur].second - arr[cur].first, dp2[i - 1][j] + arr[cur].second - arr[cur].first, dp1[i][j]});
            dp2[i][j] = max({dp1[i - 1][max(j - 1, 0)], dp2[i - 1][max(j - 1, 0)], dp2[i][j]});

            if (dp1[i][j] < 0) dp1[i][j] = -2e9;
            if (dp2[i][j] < 0) dp2[i][j] = -2e9;
        }
    }

    cout << max(dp1[n - 1][k], dp2[n - 1][k]) << "\n";

	return 0;
}
