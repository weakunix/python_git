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
    string s;
    cin >> n >> s;
    vector<int> allzero(n), allone(n);
    allzero[n - 1] = (s[n - 1] == '1');
    allone[n - 1] = (s[n - 1] == '0');
    for (int i = n - 2; i >= 0; i--) {
        if (s[i] == '0') {
            allzero[i] = allzero[i + 1];
            allone[i] = allzero[i + 1] + 1;
        }
        else {
            allone[i] = allone[i + 1];
            allzero[i] = allone[i + 1] + 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == '0') continue;
        cout << min(allone[i], allzero[i]) << "\n";
        return;
    }

    cout << "0\n";

	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
