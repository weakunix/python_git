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

const int N = 1e7 + 20;

int t;
bool works[N];
vector<int> psbl;

bool getworks(int num) {
    while (num) {
        if (num % 10 == 7) return false;
        num /= 10;
    }
    return true;
}

int main() {
    clr(works, true);

    for (int i = 1; i < N; i++) {
        if (getworks(i) or not works[i]) continue;
        for (int j = i; j < N; j += i) works[j] = false;
    }

    for (int i = 1; i < N; i++) if (works[i]) psbl.pb(i);

    cin >> t;

    for (int i = 0; i < t; i++) {
        int cur;
        cin >> cur;
        if (not works[cur]) {
            cout << "-1\n";
            continue;
        }
        cout << *ub(all(psbl), cur) << "\n";
    }

	return 0;
}
