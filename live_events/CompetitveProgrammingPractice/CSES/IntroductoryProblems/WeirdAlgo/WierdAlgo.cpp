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

int main() {
    ll n;
    cin >> n;
    cout << n << " ";
    while (n > 1) {
        if (n % 2 == 0) n /= 2;
        else n = 3 * n + 1;
        cout << n << " ";
    }
	return 0;
}
