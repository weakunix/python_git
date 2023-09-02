#include <iostream>
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

const int X = 1e6 + 1;

int n, sieve[X], ans = 1;
bool visited[X];
vector<int> divs;

void calc(int num) {
    if (num == 1) {
        divs.push_back(1);
        return;
    }
    int nxt = num, cnt = 0;
    while (nxt % sieve[num] == 0) {
        nxt /= sieve[num];
        cnt++;
    }
    calc(nxt);
    int cursz = divs.size();
    for (int i = 0; i < cursz; i++) {
        int cur = divs[i];
        for (int j = 0; j < cnt; j++) {
            cur *= sieve[num];
            if (visited[cur]) ans = max(cur, ans);
            visited[cur] = true;
            divs.push_back(cur);
        }
    }
    return;
}

int main() {
    memset(sieve, 0, sizeof(sieve));
    memset(visited, false, sizeof(visited));
    
    cin >> n;
    sieve[1] = 1;
    for (ll i = 2; i < X; i++) {
        if (sieve[i]) continue;
        sieve[i] = i;
        for (ll j = i * i; j < X; j += i) sieve[j] = i;
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        divs.clear();
        calc(x);
    }
    cout << ans << "\n";
	return 0;
}
