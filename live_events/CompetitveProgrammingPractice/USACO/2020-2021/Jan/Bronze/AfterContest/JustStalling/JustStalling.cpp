#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

#define rall(v) v.rbegin(), v.rend()

int main() {
    int N, PsblStalls = 0;
    ll Ans = 1;
    cin >> N;
    vector<int> Cows(N), Stalls(N);
    for (int i = 0; i < N; i++) cin >> Cows[i];
    for (int i = 0; i < N; i++) cin >> Stalls[i];
    sort(rall(Cows));
    sort(rall(Stalls));
    for (int i = 0; i < N; i++) {
        int CurCow = Cows[i];
        while (PsblStalls < N and Stalls[PsblStalls] >= CurCow) PsblStalls++;
        Ans *= PsblStalls - i;
    }
    cout << Ans << "\n";
    return 0;
}
