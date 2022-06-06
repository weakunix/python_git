#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("angry.out");
ifstream fin("angry.in");

long long RoundOne(double d) {
    long long ll = d * 10 + 0.5;
    return ll;
}

string PrintAns(long long Ans) {
    string StringAns = to_string(Ans);
    return StringAns.substr(0, StringAns.size() - 1) + "." + StringAns.substr(StringAns.size() - 1, 1);
}

void NegateSortVect(vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); it++) *it *= -1;
    sort(all(v));
    return;
}

map<int, int> GetMinExplosionPows(vector<int>& Haybales, int N) {
    NegateSortVect(Haybales);
    int CurPow = 0, CurHaybale = Haybales[0];
    map<int, int> MinExplosionPows = {{abs(Haybales[0]), 0}};
    for (int i = 1; i < N; i++) {
        if (Haybales[i] - CurHaybale <= CurPow) MinExplosionPows[abs(Haybales[i])] = CurPow;
        else {
            if (Haybales[i] - Haybales[i - 1] <= CurPow + 1) {
                CurHaybale = Haybales[i - 1];
                CurPow++;
            }
            else {
                CurPow = Haybales[i] - Haybales[i - 1];
                CurHaybale = Haybales[i - 1];
            }
            MinExplosionPows[abs(Haybales[i])] = CurPow;
        }
    }
    assert(MinExplosionPows.size() == N);
    return MinExplosionPows;
}

bool PossiblePow(const map<int, int>& ToLeft, const map<int, int>& ToRight, const vector<int>& Haybales, double R) {
}

int main() {
    int N;
    double Low = 0, High = 1e9;
    map<int, int> ToLeft, ToRight;
    fin >> N;
    vector<int> Haybales(N);
    for (int i = 0; i < N; i++) fin >> Haybales[i];
    ToRight = GetMinExplosionPows(Haybales, N);
    ToLeft = GetMinExplosionPows(Haybales, N);
    while (RoundOne(Low) < RoundOne(High)) {
        double Mid = Low + (High - Low) / 2;
        if (PossiblePow) High = Mid;
        else Low = Mid;
    }
    assert(RoundOne(Low) == RoundOne(High));
    fout << PrintAns(RoundOne(Low)) << "\n";
    return 0;
}
