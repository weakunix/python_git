#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int Subcase() {
    int n, x = 0, y = 0;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) x++;
        if (a[i]) y++;
        if (b[i]) y--;
    }
    return min(x, abs(y) + 1);
}

int main() {
    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) cout << Subcase() << "\n";

	return 0;
}
