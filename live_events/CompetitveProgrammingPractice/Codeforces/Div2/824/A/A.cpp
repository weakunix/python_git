#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int Subcase() {
    int n;
    cin >> n;
    return (n - 6) / 3;
}

int main() {
    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) cout << Subcase() << "\n";

	return 0;
}
