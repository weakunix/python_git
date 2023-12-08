#include <iostream>
#include <cstring>
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

const int N = 2e4;

int n, k, arr[N];

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            char c;
            cin >> c;
            if (c == '1') arr[i] ^= 1 << j;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) k = min(__builtin_popcount(arr[i] ^ arr[j]), k);
    }

    cout << k << "\n";

	return 0;
}
