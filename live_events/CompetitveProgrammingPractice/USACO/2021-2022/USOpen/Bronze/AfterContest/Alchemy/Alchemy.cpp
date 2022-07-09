#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int N, K, Ans = 0;
    unordered_map<int, vector<int> > Recipes;
    cin >> N;
    vector<int> Metals(N + 1), NeededMetals(N + 1);
    NeededMetals[N]++;
    for (int i = 1; i <= N; i++) cin >> Metals[i];
    cin >> K;
    for (int i = 0; i < K; i++) {
        int L, M;
        cin >> L >> M;
        vector<int> Ingredients(M);
        Recipes[L] = Ingredients;
        for (int j = 0; j < M; j++) cin >> Recipes[L][j];
    }
    while (true) {
        bool Done = false;
        for (int i = N; i > 0; i--) {
            if (Metals[i] < NeededMetals[i]) {
                if (Recipes.count(i) == 0) {
                    Done = true;
                    break;
                }
                for (int j : Recipes[i]) {
                    Metals[j] += Metals[i];
                    NeededMetals[j] += NeededMetals[i];
                }
                NeededMetals[i] = 0;
            }
            else Metals[i] -= NeededMetals[i];
        }
        if (Done) break;
        Ans++;
    }
    cout << Ans << "\n";
    return 0;
}
