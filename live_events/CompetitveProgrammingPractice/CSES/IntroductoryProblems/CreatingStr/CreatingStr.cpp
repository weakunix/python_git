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

string s;
vector<string> ans;

int main() {
    cin >> s;
    sort(all(s));
    ans.push_back(s);
    while (next_permutation(all(s))) ans.push_back(s);
    cout << ans.size() << "\n";
    for (string& t : ans) cout << t << "\n";
	return 0;
}
