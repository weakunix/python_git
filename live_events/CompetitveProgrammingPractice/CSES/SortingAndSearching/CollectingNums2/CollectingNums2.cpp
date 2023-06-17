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

int n, m, ans = 0;
vector<int> arr, idx;

int main() {
    cin >> n >> m;
    arr.resize(n + 1);
    idx.resize(n + 2);
    idx[0] = 1e9; idx[n + 1] = 1e9;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        idx[arr[i]] = i;
    }
    for (int i = 1; i <= n; i++) ans += (idx[i] < idx[i - 1]);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (a != b) {
            if (arr[a] > arr[b]) swap(a, b);
            if (arr[a] + 1 == arr[b]) {
                for (int i = arr[a]; i <= arr[b] + 1; i++) ans -= (idx[i] < idx[i - 1]);
                swap(idx[arr[a]], idx[arr[b]]);
                swap(arr[a], arr[b]);
                for (int i = arr[b]; i <= arr[a] + 1; i++) ans += (idx[i] < idx[i - 1]);
            }
            else {
                for (int i = arr[a]; i <= arr[a] + 1; i++) ans -= (idx[i] < idx[i - 1]);
                for (int i = arr[b]; i <= arr[b] + 1; i++) ans -= (idx[i] < idx[i - 1]);
                swap(idx[arr[a]], idx[arr[b]]);
                swap(arr[a], arr[b]);
                for (int i = arr[a]; i <= arr[a] + 1; i++) ans += (idx[i] < idx[i - 1]);
                for (int i = arr[b]; i <= arr[b] + 1; i++) ans += (idx[i] < idx[i - 1]);
            }
        }
        cout << ans << "\n";
    }
	return 0;
}
