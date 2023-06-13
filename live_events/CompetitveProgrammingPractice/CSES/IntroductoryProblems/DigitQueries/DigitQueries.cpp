#include <iostream>
#include <string>
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

int t;
vector<ll> pow10 = {1};

void subcase() {
    int dig = 1;
	ll n;
    cin >> n;
    while (n > dig * (pow10[dig] - pow10[dig - 1])) {
        n -= dig * (pow10[dig] - pow10[dig - 1]);
        dig++;
    }
    cout << to_string(pow10[dig - 1] + (n - 1) / dig)[n - (n - 1) / dig * dig - 1] << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
    for (int i = 0; i < 18; i++) pow10.push_back(10 * pow10[i]);
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
