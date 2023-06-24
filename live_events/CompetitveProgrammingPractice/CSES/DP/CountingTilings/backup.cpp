#include <iostream>
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

const int modval = 1e9 + 7;

int n, m;
vector<vector<int>> adj;

bool works(int a, int b) {
    for (int i = 0; i < n; i++) {
        if (a & (1 << i)) {
            if (b & (1 << i))
        }
    }
}

int main() {
    cin >> n >> m;
    adj.resize(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < (1 << n); j++) {
            if (works(i, j)) adj[i].push_back(j);
        }
    }
	return 0;
}
