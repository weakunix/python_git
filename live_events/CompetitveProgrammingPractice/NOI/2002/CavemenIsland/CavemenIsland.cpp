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

const int N = 15;

int n, m = 0, x, y;
threesome arr[N];

int exgcd(int a, int b) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int g = exgcd(b, a % b), prvx = x;
    x = y;
    y = prvx - y * (a / b);
    return g;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].sec >> arr[i].third;
        setmx(m, arr[i].first);
        arr[i].first--;
    }

    while (true) {
        bool works = true;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int p = arr[i].sec - arr[j].sec, c = arr[j].first - arr[i].first;
                if (p == 0) continue;
                if (p < 0) {
                    p = -p;
                    c = -c;
                }

                int g = exgcd(p, m);
                if (c % g) continue;
                x *= (c / g);

                if ((x % (m / g) + (m / g)) % (m / g) <= min(arr[i].third, arr[j].third)) {
                    works = false;
                    break;
                }
            }

            if (not works) break;
        }

        if (works) {
            cout << m << "\n";
            return 0;
        }

        m++;
    }

	return 0;
}
