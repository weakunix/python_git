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

int n, mn, ans = 0;
multiset<int> s;

int main() {
    cin >> n >> mn;
    for (int i = 0; i < n; i++) {
        int k;
        char t;
        cin >> t >> k;

        if (t == 'I') {
            if (k < mn) continue;
            s.insert(k);
        }
        else if (t == 'A') {
            multiset<int> nws;
            for (int i : s) nws.insert(i + k);
            swap(nws, s);
        }
        else if (t == 'S') {
            multiset<int> nws;
            for (int i : s) {
                if (i - k < mn) ans++;
                else nws.insert(i - k);
            }
            swap(nws, s);
        }
        else {
            bool works = true;
            auto it = s.end();
            for (int i = 0; i < k; i++) {
                if (it == s.begin()) {
                    works = false;
                    break;
                }
                it--;
            }
            cout << (works ? *it : -1) << "\n";
        }
    }
    cout << ans << "\n";
	return 0;
}
