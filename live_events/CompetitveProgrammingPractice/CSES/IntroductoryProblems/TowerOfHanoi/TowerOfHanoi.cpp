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

const vector<int> ltom = {0, 1, 3, 2}, mtor = {0, 2, 1, 3};

int n;
vector<simps> prv = {{1, 3}};

int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        vector<simps> cur;
        for (simps& s : prv) cur.push_back({ltom[s.first], ltom[s.second]});
        cur.push_back({1, 3});
        for (simps& s : prv) cur.push_back({mtor[s.first], mtor[s.second]});
        swap(cur, prv);
    }
    cout << prv.size() << "\n";
    for (simps& s : prv) cout << s.first << " " << s.second << "\n";
	return 0;
}
