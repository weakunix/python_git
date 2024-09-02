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

const vector<simps> one = {{2, 3}, {3, 2}, {3, 5}, {5, 3}, {0, 6}, {6, 0}, {0, 9}, {9, 0}, {6, 9}, {9, 6}};
const vector<simps> two = {{1, 7}, {3, 9}, {5, 6}, {5, 9}, {0, 8}, {6, 8}, {9, 8}};

int idx[2][10][10];
ll tar = 0;
string ans;

void inpt() {
    string s;
    cin >> s;

    bool eq = false, pos = true;
    string cur;
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        ans += c;

        if (c >= '0' and c <= '9') {
            cur += c;
            continue;
        }
        
        if (cur.empty()) {
            if (c == '-') pos = not pos;
            continue;
        }

        if (eq) pos = not pos;
        tar += stoi(cur) * (pos ? 1 : -1);
        for (int j = 0; j < cur.size(); j++) idx[pos][j][s[i - 1 - j] - '0'] = i - 1 - j;

        cur.clear();
        pos = true;
        if (c == '-') pos = false;
        if (c == '=') eq = true;
        if (c == '#') break;
    }

    tar = -tar;

    return;
}

int main() {
    clr(idx, -1);

    inpt();

    for (simps change : one) {
        for (int pos = 0; pos < 2; pos++) {
            for (int pwidx = 0, pw = 1; pwidx < 10; pwidx++, pw *= 10) {
                if (idx[pos][pwidx][change.first] == -1) continue;
                if ((pos ? 1ll : -1ll) * (change.second - change.first) * pw != tar) continue;
                ans[idx[pos][pwidx][change.first]] = '0' + change.second;
                cout << ans << "\n";
                return 0;
            }
        }
    }

    for (simps pch : two) {
        for (simps nch: two) {
            for (int ppos = 0; ppos < 2; ppos++) {
                for (int npos = 0; npos < 2; npos++) {
                    for (int ppwidx = 0, ppw = 1; ppwidx < 10; ppwidx++, ppw *= 10) {
                        for (int npwidx = 0, npw = 1; npwidx < 10; npwidx++, npw *= 10) {
                            if (idx[ppos][ppwidx][pch.first] == -1) continue;
                            if (idx[npos][npwidx][nch.second] == -1) continue;
                            ll a = (ppos ? 1ll : -1ll) * (pch.second - pch.first) * ppw;
                            ll b = (npos ? 1ll : -1ll) * (nch.first - nch.second) * npw;
                            if (a + b != tar) continue;
                            ans[idx[ppos][ppwidx][pch.first]] = '0' + pch.second;
                            ans[idx[npos][npwidx][nch.second]] = '0' + nch.first;
                            cout << ans << "\n";
                            return 0;
                        }
                    }
                }
            }
        }
    }

    cout << "No\n";

	return 0;
}
