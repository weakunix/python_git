#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("sabotage.out");
ifstream fin("sabotage.in");

int RoundThreePlaces(double d) {
    return d * 1000 + 0.5;
}

bool IsValidAvg(const vector<int>& Machines, double Avg, int N) {
    double Best = Machines[1] - Avg, Cur = 0, Total = 0;
    for (int i = 0; i < N; i++) {
        Total += Machines[i] - Avg;
        if (i != 0 and i != N - 1) {
            Cur = max(Machines[i] - Avg, Cur + Machines[i] - Avg);
            Best = max(Cur, Best);
        }
    }
    return Best >= Total;
}

string PrintAns(int Ans) {
    string FinalAns = to_string(Ans);
    return FinalAns.substr(0, FinalAns.size() - 3) + '.' + FinalAns.substr(FinalAns.size() - 3, 3);
}

int main() {
    int N;
    double Low = 1, High = 10000;
    fin >> N;
    vector<int> Machines(N);
    for (int i = 0; i < N; i++) fin >> Machines[i];
    while (RoundThreePlaces(Low) < RoundThreePlaces(High)) {
        double Mid = Low + (High - Low) / 2;
        if (IsValidAvg(Machines, Mid, N)) High = Mid;
        else Low = Mid;
    }
    fout << PrintAns(RoundThreePlaces(Low)) << "\n";
    return 0;
}
