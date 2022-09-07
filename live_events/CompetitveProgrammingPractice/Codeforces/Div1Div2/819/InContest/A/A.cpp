#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int Subcase() {
    int N, Ans;
    cin >> N;
    vector<int> Nums(N);
    for (int i = 0; i < N; i++) cin >> Nums[i];
    Ans = Nums.back() - Nums[0];

    for (int i = 1; i < N; i++) Ans = max(Nums[i] - Nums[0], Ans);
    for (int i = 0; i < N - 1; i++) Ans = max(Nums.back() - Nums[i], Ans);

    for (int i = 0; i < N; i++) Ans = max(Nums[(i + N - 1) % N] - Nums[i], Ans);

    return Ans;
}

int main() {
    //freopen("test.in", "r", stdin);
    
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) cout << Subcase() << "\n";

    return 0;
}
