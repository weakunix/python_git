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

int n;

int main() {
    cin >> n;
    if (n == 1) {
        cout << "1\n";
        return 0;
    }
    if (n < 4) {
        cout << "NO SOLUTION\n";
        return 0;
    }
    if (n == 4) {
        cout << "3 1 4 2\n";
        return 0;
    }
    for (int i = 1; i < (n + 1) / 2; i++) cout << i << " " << i + (n + 1) / 2 << " ";
    if (n % 2 == 0) cout << n / 2 << " " << n;
    else cout << (n + 1) / 2;
    cout << "\n";
	return 0;
}
