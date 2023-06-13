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

int cnt = 0, ans = 0;
char last = 'A';
string s;

int main() {
    cin >> s;
    for (char c : s) {
        if (c == last) cnt++;
        else {
            ans = max(cnt, ans);
            cnt = 1;
            last = c;
        }
    }
    cout << max(cnt, ans) << "\n";
	return 0;
}
