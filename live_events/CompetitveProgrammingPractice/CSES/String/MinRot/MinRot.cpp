#include <iostream>
#include <string>
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

int n, ans = 0;
string s;

int main() {
    cin >> s;
    n = s.size();
    s += s;
    for (int i = 0; i < n;) {
        int j = i + 1, k = i;
        ans = i;
        while (j < 2 * n and s[j] >= s[k]) {
            if (s[j] == s[k]) k++;
            else k = i;
            j++;
        }
        while (i <= k) i += j - k;
    }
    cout << s.substr(ans, n) << "\n";
	return 0;
}
