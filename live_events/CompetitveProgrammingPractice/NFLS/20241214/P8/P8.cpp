#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int L = 31;

int t;
bool a[L], b[L], k[L], w[L];
ll dp[L][2][2][2][3][3], ans; // digit, a, b, w, y+k-x, x+k-y

void procinpt() {
    int ai, bi, ki, wi;
    cin >> ai >> bi >> ki >> wi;
    for (int i = 0; i < L; i++) {
        a[i] = (ai & (1 << i));
        b[i] = (bi & (1 << i));
        k[i] = (ki & (1 << i));
        w[i] = (wi & (1 << i));
    }
    return;
}

void subcase() {
    clr(dp, 0);
    ans = 0;

    procinpt();

    dp[0][1][1][1][1][1] = 1;

    for (int i = 0; i < L - 1; i++) {
        for (int p = 0; p < 2; p++) {
            for (int q = 0; q < 2; q++) {
                for (int r = 0; r < 2; r++) {
                    for (int s = 0; s < 3; s++) {
                        for (int u = 0; u < 3; u++) {
                            for (int j = 0; j < 2; j++) {
                                for (int l = 0; l < 2; l++) {
                                    int newp, newq, newr, news, newu;
                                    
                                    if (a[i] > j) newp = 1;
                                    else if (a[i] < j) newp = 0;
                                    else newp = p;

                                    if (b[i] > l) newq = 1;
                                    else if (b[i] < l) newq = 0;
                                    else newq = q;

                                    if (w[i] > (j ^ l)) newr = 1;
                                    else if (w[i] < (j ^ l)) newr = 0;
                                    else newr = r;

                                    int cur = l - j + k[i] + (s - 1);
                                    if (cur < 0) news = 0;
                                    else if (cur >= 2) news = 2;
                                    else news = 1;

                                    cur = j - l + k[i] + (u - 1);
                                    if (cur < 0) newu = 0;
                                    else if (cur >= 2) newu = 2;
                                    else newu = 1;

                                    dp[i + 1][newp][newq][newr][news][newu] += dp[i][p][q][r][s][u];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    for (int s = 1; s < 3; s++) {
        for (int u = 1; u < 3; u++) {
            ans += dp[L - 1][1][1][1][s][u];
        }
    }

    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
