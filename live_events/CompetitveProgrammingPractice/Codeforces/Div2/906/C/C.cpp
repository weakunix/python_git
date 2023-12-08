#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
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

int t;

void subcase() {
    int n;
    vector<int> ans;
    deque<bool> s;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        s.push_back(c == '1');
    }

    if (n % 2 == 1) {
        cout << "-1\n";
        return;
    }

    int l = 0, r = n - 1;
    while (l < r and ans.size() <= 300) {
        assert(s.size() >= 2);

        if (s.front() != s.back()) {
            l++;
            r--;
            s.pop_front();
            s.pop_back();
            continue;
        }

        if (s.front()) {
            ans.push_back(l);
            s.push_front(true);
            s.push_front(false);
            r += 2;
        }
        else {
            ans.push_back(r + 1);
            s.push_back(false);
            s.push_back(true);
            r += 2;
        }
    }

    if (ans.size() > 300) cout << "-1\n";
    else {
        cout << ans.size() << "\n";
        for (int i : ans) cout << i << " ";
        cout << "\n";
    }

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
