#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
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

const int N = 2e5 + 1;

int n, seq[N], indeg[N];
priority_queue<int> pq;

int main() {
    memset(indeg, 0, sizeof(indeg));

    cin >> n;
    for (int i = 0; i < n - 2; i++) {
        cin >> seq[i];
        indeg[seq[i]]++;
    }
    seq[n - 2] = seq[n - 3];
    indeg[seq[n - 2]]++;

    for (int i = 1; i <= n; i++) if (not indeg[i]) pq.push(-i);

    for (int i = 0; i < n - 1; i++) {
        int cur = -pq.top();
        pq.pop();
        cout << cur << " " << seq[i] << "\n";
        indeg[seq[i]]--;
        if (not indeg[seq[i]]) pq.push(-seq[i]);
    }

	return 0;
}
