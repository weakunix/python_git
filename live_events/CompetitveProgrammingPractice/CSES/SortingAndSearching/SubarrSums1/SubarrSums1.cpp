#include <iostream>
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

int n, tar, l = 0, r = 0, cur = 0, ans = 0;
vector<int> arr;

int main() {
    cin >> n >> tar;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    cur = arr[0];
    while (r < n) {
        ans += (cur == tar);
        if (cur <= tar) {
            r++;
            cur += arr[r];
        }
        else {
            cur -= arr[l];
            l++;
        }
    }
    cout << ans << "\n";
	return 0;
}
