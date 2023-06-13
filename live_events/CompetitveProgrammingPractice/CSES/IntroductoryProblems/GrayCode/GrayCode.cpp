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

int n;
vector<string> prv = {"0", "1"};

int main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        vector<string> cur;
        for (int j = 0; j < (1 << i); j++) cur.push_back("0" + prv[j]);
        for (int j = (1 << i) - 1; j >= 0; j--) cur.push_back("1" + prv[j]);
        swap(prv, cur);
    }
    for (string& s : prv) cout << s << "\n";
	return 0;
}
