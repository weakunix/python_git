#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

void subcase() {
    int n, ans = 0;
    vector<int> arr, count;
    cin >> n;
    arr.resize(n);
    count.resize(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        count[arr[i]]++;
    }
    while (n > 0) {
        int cur = -1;
        bool done = false;
        for (int i = 0; i < n; i++) {
            int prev = ((i == 0) ? n - 1 : i - 1), next = ((i == n - 1) ? 0 : i + 1);
            if (count[arr[i]] == 1) {
                done = true;
                break;
            }
            if (arr[prev] != arr[next]) {
                cur = i;
                break;
            }
        }
        if (done) break;
        if (cur != -1) {
            count[arr[cur]]--;
            arr.erase(arr.begin() + cur);
        }
        else {
            count[arr[0]]--;
            arr.erase(arr.begin());
            count[arr[0]]--;
            arr.erase(arr.begin());
        }
        n = arr.size();
        ans++;
    }
    cout << ans + n << "\n";
    return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
