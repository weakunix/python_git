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

int n, tar;
vector<simps> arr;

bool works(int st) {
    int curtar = tar - arr[st].first, l = st + 1, r = n - 1;
    while (l < r) {
        int cur = arr[l].first + arr[r].first;
        if (cur == curtar) {
            cout << arr[st].second << " " << arr[l].second << " " << arr[r].second << "\n";
            return true;
        }
        if (cur < curtar) l++;
        else r--;
    }
    return false;
}

int main() {
    cin >> n >> tar;
    arr.resize(n);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i - 1].first;
        arr[i - 1].second = i;
    }
    sort(all(arr));
    for (int i = 0; i < n - 2; i++) {
        if (works(i)) return 0;
    }
    cout << "IMPOSSIBLE\n";
	return 0;
}
