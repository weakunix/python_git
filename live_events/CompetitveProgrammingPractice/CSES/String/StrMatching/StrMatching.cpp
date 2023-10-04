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

const int m1 = 1e9 + 7, m2 = 1e9 + 9, H = 101;

int n, m, ans = 0;
ll cur1 = 0, cur2 = 0, tar1 = 0, tar2 = 0, rem1 = 1, rem2 = 1;
string big, tar;

int main() {
    cin >> big >> tar;
    n = big.size();
    m = tar.size();
    if (m > n) {
        cout << "0\n";
        return 0;
    }
    for (int i = 0; i < m; i++) {
        cur1 = (cur1 * H % m1 + (big[i] - 'a') + 1) % m1;
        cur2 = (cur2 * H % m2 + (big[i] - 'a') + 1) % m2;
        tar1 = (tar1 * H % m1 + (tar[i] - 'a') + 1) % m1;
        tar2 = (tar2 * H % m2 + (tar[i] - 'a') + 1) % m2;
        rem1 = rem1 * H % m1;
        rem2 = rem2 * H % m2;
    }
    ans += (cur1 == tar1 and cur2 == tar2);
    for (int i = m; i < n; i++) {
        cur1 = (cur1 * H % m1 + (big[i] - 'a') + 1) % m1;
        cur2 = (cur2 * H % m2 + (big[i] - 'a') + 1) % m2;
        cur1 = (cur1 + m1 - rem1 * ((big[i - m] - 'a') + 1) % m1) % m1;
        cur2 = (cur2 + m2 - rem2 * ((big[i - m] - 'a') + 1) % m2) % m2;
        ans += (cur1 == tar1 and cur2 == tar2);
    }
    cout << ans << "\n";
	return 0;
}
