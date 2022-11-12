#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

void subcase() {
    int n, shift = 0;
    queue<int> consider;
    map<int, int> count;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        map[arr[i]]++;
        if (arr[i] == 0) consider.push(i);
    }
    for (int i = 0; i < n; i++) {
        if (not consider.empty() and consider.front() == i) {
            consider.pop();
        }
        count[arr[i]]--;
    }
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
