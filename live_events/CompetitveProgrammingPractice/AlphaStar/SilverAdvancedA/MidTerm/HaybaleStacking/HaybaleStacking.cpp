#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> Haybales(N + 1);
    for (int i = 0; i < K; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        Haybales[a]++;
        Haybales[b + 1]--;
    }
    for (int i = 1; i <= N; i++) Haybales[i] += Haybales[i - 1];
    Haybales.pop_back();
    sort(all(Haybales));
    cout << Haybales[N / 2] << "\n";
    return 0;
}
