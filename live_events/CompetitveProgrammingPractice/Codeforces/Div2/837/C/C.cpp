#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>
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

vector<int> primes;

void genprimes() {
    for (int i = 2; i * i <= 1e9; i++) {
        bool works = true;
        for (int j : primes) {
            if (i % j != 0) continue;
            works = false;
            break;
        }
        if (works) primes.push_back(i);
    }
    return;
}

void subcase() {
    int n;
    vector<int> arr;
    set<int> found;
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i : arr) {
        int cur = i;
        for (int j : primes) {
            if (j * j > i) break;
            if (cur % j == 0) {
                if (found.count(j) > 0) {
                    cout << "YES\n";
                    return;
                }
                found.insert(j);
            }
            while (cur % j == 0) cur /= j;
        }
        if (cur == 1) continue;
        if (found.count(cur) > 0) {
            cout << "YES\n";
            return;
        }
        found.insert(cur);
    }
    cout << "NO\n";
	return;
}

int main() {
	int t;
	cin >> t;
    genprimes();
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
