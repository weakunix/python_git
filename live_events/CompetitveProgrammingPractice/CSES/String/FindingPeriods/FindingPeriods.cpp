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

const int N = 1e6 + 1;

int n, z[N];
string s;

void genz() {
    int l = 0, r = 1;
    for (int i = 1; i < n; i++) {
        if (i + z[i - l] < r) z[i] = z[i - l];
        else {
            l = i;
            if (r < i) r = i;
            while (r < n and s[r] == s[r - l]) r++;
            z[i] = r - l;
        }
    }
    return;
}

int main() {
    memset(z, 0, sizeof(z));

    cin >> s;
    n = s.size();
    genz();
    for (int i = 1; i <= n; i++) {
        bool works = true;
        for (int j = i; j < n; j += i) {
            if (z[j] < i and z[j] != n - j) {
                works = false;
                break;
            }
        }
        if (works) cout << i << " ";
    }
    cout << "\n";
	return 0;
}
