#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n;
vector<int> p, in;

int main() {
    cin >> n;
    p.resize(n);
    in.resize(n);
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        p[i]--;
        in[p[i]]++;
    }

	return 0;
}
