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

const int N = 250, K = 200, L = 30;

struct Mat {
    int r, c;
    ll arr[N][N];

    Mat() : r(0), c(0) {
        clr(arr, -1);
    }

    Mat(int _r, int _c) : r(_r), c(_c) {
        clr(arr, -1);
    }

    ~Mat() {}

    void dbg() {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) cout << arr[i][j] << " ";
            cout << "\n";
        }
    }
};

int n, m, t, k, val[N], prvt = 0;
threesome events[K];
Mat tmat[L], ans;

Mat matmul(Mat& a, Mat& b) {
    assert(a.c == b.r);
    Mat res = Mat(a.r, b.c);
    for (int i = 0; i < a.r; i++) {
        for (int j = 0; j < b.c; j++) {
            for (int l = 0; l < a.c; l++) {
                if (a.arr[i][l] == -1 or b.arr[l][j] == -1) continue;
                setmx(res.arr[i][j], a.arr[i][l] + b.arr[l][j]);
            }
        }
    }
    return res;
}

void pw(int curt) {
    int cnt = 0;
    while (curt) {
        if (curt & 1) ans = matmul(ans, tmat[cnt]);
        cnt++;
        curt >>= 1;
    }
    return;
}

int main() {
    cin >> n >> m >> t >> k;
    n *= 5;
    tmat[0] = Mat(n, n);
    for (int i = 0; i < n; i++) if (i % 5) tmat[0].arr[i][i - 1] = 0;

    for (int i = 0; i < n; i += 5) cin >> val[i];

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a = 5 * (a - 1);
        b = 5 * (b - 1);
        w--;
        tmat[0].arr[a][b + w] = val[b];
    }
    for (int i = 1; i < L; i++) tmat[i] = matmul(tmat[i - 1], tmat[i - 1]);

    for (int i = 0; i < k; i++) cin >> events[i].first >> events[i].sec >> events[i].third;
    sort(events, events + k);
    
    ans = Mat(1, n);
    ans.arr[0][0] = val[0];

    for (int i = 0; i < k; i++) {
        int curt = events[i].first, x = 5 * (events[i].sec - 1), y = events[i].third;
        pw(curt - prvt);
        prvt = curt;
        if (ans.arr[0][x] != -1) ans.arr[0][x] += y;
    }

    pw(t - prvt);
    cout << ans.arr[0][0] << "\n";

	return 0;
}
