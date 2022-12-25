#include <iostream>
#include <string>
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

vector<int> mod1p, mod3p;

bool isprime(int num) {
    for (int i : mod1p) {
        if (i == 1) continue;
        if (i * i > num) break;
        if (num % i == 0) return false;
    }
    for (int i : mod3p) {
        if (i * i > num) break;
        if (num % i == 0) return false;
    }
    return true;
}

void precomp() {
    for (int i = 1; i <= 5e6; i += 2) {
        if (not isprime(i)) continue;
        if (i % 4 == 1) mod1p.push_back(i);
        else mod3p.push_back(i);
    }
    return;
}

void subcase() {
    int n;
    simps fj = {1e9, 1e9}, fn = {1e9, 1e9};
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        if (cur % 4 == 0) {
            fn = min(make_pair(cur / 4 + 1, i), fn);
            continue;
        }
        if (cur % 4 == 2) {
            fj = min(make_pair(cur / 4 + 1, i), fj);
            continue;
        }
        if (cur % 4 == 1) {
            auto it = upper_bound(all(mod1p), cur);
            it--;
            fj = min(make_pair((cur - *it) / 4 + 1, i), fj);
            continue;
        }
        auto it = upper_bound(all(mod3p), cur);
        it--;
        fj = min(make_pair((cur - *it) / 4 + 1, i), fj);
    }
    cout << ((fj < fn) ? "Farmer John\n" : "Farmer Nhoj\n");
	return;
}

int main() {
    precomp();
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
