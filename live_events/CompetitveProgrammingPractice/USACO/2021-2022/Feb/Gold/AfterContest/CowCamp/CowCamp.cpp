#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

double GetChoose(const int N, const int Total, int DividePower) {
    double Res = 1;
    for (int i = 1; i <= N; i++) {
        Res *= Total - i + 1;
        Res /= i;
        while (DividePower > 0 and Res > 1) {
            Res /= 2;
            DividePower--;
        }
    }
    for (int i = 0; i < DividePower; i++) Res /= 2;
    assert(Res <= 1);
    return Res;
}

double GetUnderMultiplier(const double UnderProb, const int K) {
    double Res = 1;
    for (int i = 0; i < K - 1; i++) Res *= UnderProb;
    return Res;
}

double GetOverMultiplier(const double UnderProb, const double UnderMultiplier) {
    return (1 - UnderMultiplier * UnderProb) / (1 - UnderProb);
}

int main() {
    int T, K, ExpectedValFloor;
    double ExpectedVal = 0, UnderProb = 0, UnderMultiplier, OverMultiplier, Ans = 0;
    vector<double> Probs;
    cin >> T >> K;
    for (int i = 0; i < T; i++) Probs.push_back(GetChoose(i, T - 1, T - 1));
    for (int i = 0; i < T; i++) ExpectedVal += (i + 1) * Probs[i];
    ExpectedValFloor = ExpectedVal;
    for (int i = 0; i < ExpectedValFloor; i++) UnderProb += Probs[i];
    UnderMultiplier = GetUnderMultiplier(UnderProb, K);
    OverMultiplier = GetOverMultiplier(UnderProb, UnderMultiplier);
    for (int i = 0; i < ExpectedValFloor; i++) Ans += (i + 1) * UnderMultiplier * Probs[i];
    for (int i = ExpectedValFloor; i < T; i++) Ans += (i + 1) * OverMultiplier * Probs[i];
    cout << Ans << "\n";
    return 0;
}
