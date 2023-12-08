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

int m, p, q;
vector<int> mul;

int main() {
    cin >> m >> p;
    for (int i = 0; i < p; i++) {
        int cur;
        cin >> cur;
        mul.push_back(cur);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int cur;
        cin >> cur;
        m += cur;
    }
    for (int i : mul) m *= i;
    cout << m << "\n";
	return 0;
}
