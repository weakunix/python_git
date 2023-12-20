#include <iostream>
#include <cstring>
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

int n;
vector<simps> ans;
set<simps> st;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int cur;
        cin >> cur;
        st.insert({cur, i});
    }

    while (st.size()) {
        int cur = st.begin()->second, cnt = st.begin()->first;
        vector<simps> nw;

        st.erase({cnt, cur});
        for (int i = 0; i < cnt; i++) {
            if (st.empty()) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }

            auto it = st.end();
            it--;
            ans.push_back({cur, it->second});
            nw.push_back({it->first - 1, it->second});
            st.erase(it);
        }
        for (simps s : nw) st.insert(s);
    }

    cout << ans.size() << "\n";
    for (simps s : ans) cout << s.first << " " << s.second << "\n";

	return 0;
}
