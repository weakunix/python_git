#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <map>
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

int n = 0;
string s, ans;
map<char, int> cnt;
map<int, set<char>> force;

int main() {
    cin >> s;
    n = s.size();
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (auto& u : cnt) {
        if (u.second > (n + 1) / 2) {
            cout << "-1\n";
            return 0;
        }
        force[u.second].insert(u.first);
    }
    
    while (n) {
        int cur = (n + 1) / 2;
        if (n % 2 and force.count(cur)) {
            assert(force[cur].size() == 1);
            char c = *force[cur].begin();
            ans += c;
            force.erase(cur);
            force[cur - 1].insert(c);
            cnt[c]--;
            n--;
            continue;
        }

        for (auto& u : cnt) {
            int cur = u.second;
            char c = u.first;
            if (not ans.empty() and ans.back() == c) continue;
            ans += c;
            force[cur].erase(c);
            if (force[cur].empty()) force.erase(cur);
            cnt[c]--;

            if (cnt[c] > 0) force[cnt[c]].insert(c);
            else cnt.erase(c);
            break;
        }

        n--;
    }

    cout << ans << "\n";

	return 0;
}
