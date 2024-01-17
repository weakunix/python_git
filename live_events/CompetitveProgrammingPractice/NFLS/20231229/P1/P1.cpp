#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <deque>
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

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 250001, modval = 998244353;

int n, m;
ll ans = 1, mul = 0, cnt = 0;
bool seen[N], placed[N];
deque<int> arr;

int main() {
    //freopen("per.in", "r", stdin);
    //freopen("per.out", "w", stdout);

    memset(seen, false, sizeof(seen));
    memset(placed, false, sizeof(placed));

    cin >> n >> m;
    arr.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> arr[i];
        seen[arr[i]] = true;
    }

    for (int i = 1; i <= n; i++) {
        if (placed[i]) continue;
        cnt++;

        if (arr.empty()) {
            ans = ans * cnt % modval;
            continue;
        }

        if (not seen[i]) {
            if (not mul) {
                cout << "0\n";
                return 0;
            }
            ans = ans * mul % modval;
            mul++;
            continue;
        }
        
        if (arr.front() == i) {
            mul++;
            arr.pop_front();
            continue;
        }

        while (arr.back() != i) {
            placed[arr.back()] = true;
            arr.pop_back();
        }
        arr.pop_back();
        cnt--;
    }

    cout << ans << "\n";

	return 0;
}
