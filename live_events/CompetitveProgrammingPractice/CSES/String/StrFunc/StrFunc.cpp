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

const int N = 1e6;

int n, z[N], kmp[N];
string s;

void genz() {
    int l = 0, r = 1;
    z[0] = 0;

    for (int i = 1; i < n; i++) {
        if (r <= i) {
            l = i;
            r = i;
            while (r < n and s[r] == s[r - l]) r++;
            z[i] = r - l;
            continue;
        }
        if (z[i - l] + i < r) {
            z[i] = z[i - l];
            continue;
        }
        l = i;
        while (r < n and s[r] == s[r - l]) r++;
        z[i] = r - l;
    }

    return;
}

void genkmp() {
    int j = 0;
    kmp[0] = 0;

    for (int i = 1; i < n; i++) {
        while (j != -1) {
            if (s[j] == s[i]) {
                j++;
                break;
            }
            if (j == 0) break;
            j = kmp[j - 1];
        }
        kmp[i] = j;
    }
    return;
}

int main() {

    cin >> s;
    n = s.size();

    genz();
    genkmp();

    for (int i = 0; i < n; i++) cout << z[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) cout << kmp[i] << " ";
    cout << "\n";

	return 0;
}
