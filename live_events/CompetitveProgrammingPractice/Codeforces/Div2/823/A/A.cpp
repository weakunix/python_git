#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int Subcase() {
    int N, C, Res = 0;
    vector<int> Count(101);
    cin >> N >> C;
    for (int i = 0; i < N; i++) {
        int Cur;
        cin >> Cur;
        Count[Cur]++;
    }

    for (int i : Count) Res += min(i, C);

    return Res;
}

int main() {
    int T;
    cin >> T;
    
    for (int i = 0; i < T; i++) cout << Subcase() << "\n";

	return 0;
}
