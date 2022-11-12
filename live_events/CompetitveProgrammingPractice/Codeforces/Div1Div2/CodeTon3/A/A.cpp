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
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    if (arr[0] == 1) cout << "YES\n";
    else cout << "NO\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
