#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

struct slope {
    int x, y;
};

bool operator<=(slope a, slope b) {
    return ((ll) a.y * b.x <= (ll) b.y * a.x);
}

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n, q;
vector<int> hgt;
vector<set<pair<int, slope>>> arr;

int main() {
    cin >> n;
    hgt.resize(n);
    arr.resize(n - 1);
    for (int i = 0; i < n; i++) cin >> hgt[i];
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            slope curslope = {j - i, hgt[j] - hgt[i]};
            if (arr[i].empty() or arr[i].rend()->second <= curslope) arr[i].insert({j - i, curslope});
        }
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
    }
	return 0;
}
