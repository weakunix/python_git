#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

string Subcase() {
    int n;
    string t, ans = "";
    cin >> n >> t;
    vector<int> mapping(26, -1);
    set<int> left;
    for (int i = 0; i < 26; i++) left.insert(i);
    
    for (char c : t) {
        int cur = c - 'a';
        if (mapping[cur] == -1) {
            if (left.size() == 2 and mapping[*left.rbegin()] == -1) {
                mapping[cur] = *left.rbegin();
                left.erase(mapping[cur]);
            }
            else {
                if (*left.begin() == cur) {
                    auto it = left.upper_bound(cur);
                    assert(it != left.end());
                    mapping[cur] = *it;
                    left.erase(mapping[cur]);
                }
                else {
                    mapping[cur] = *left.begin();
                    left.erase(mapping[cur]);
                }
            }
        }
        ans += (char) (mapping[cur] + 'a');
    }

    return ans;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) cout << Subcase() << "\n";

	return 0;
}
