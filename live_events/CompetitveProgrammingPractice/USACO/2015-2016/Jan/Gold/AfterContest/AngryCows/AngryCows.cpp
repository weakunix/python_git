#include <fstream>
#include <string>
#include <vector>
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

int PossibleLoc(vector<int> LeftHaybales, double R, double Loc) {
    int Res = 0;
    double TempR = R, LastHaybale = Loc;
    vector<int> RightHaybales;
    while (LeftHaybales.size() > 0 and LeftHaybales.back() > Loc) {
        RightHaybales.push_back(LeftHaybales.back());
        LeftHaybales.pop_back();
    }
    if (LeftHaybales.back() == Loc) LeftHaybales.pop_back();
    while (LeftHaybales.size() > 0 and TempR > 0) {
        bool EndEarly = true;
        double CurRangeEnd = LastHaybale - TempR;
        while (LeftHaybales.size() > 0 and LeftHaybales.back() >= CurRangeEnd) {
            EndEarly = false;
            LastHaybale = LeftHaybales.back();
            LeftHaybales.pop_back();
        }
        if (EndEarly) break;
        TempR--;
    }
    if (LeftHaybales.size() == 0) Res++;
    TempR = R;
    LastHaybale = Loc;
    while (RightHaybales.size() > 0 and TempR > 0) {
        bool EndEarly = true;
        double CurRangeEnd = LastHaybale + TempR;
        while (RightHaybales.size() > 0 and RightHaybales.back() <= CurRangeEnd) {
            EndEarly = false;
            LastHaybale = RightHaybales.back();
            RightHaybales.pop_back();
        }
        if (EndEarly) break;
        TempR--;
    }
    if (RightHaybales.size() == 0) Res += 2;
    return Res;
}

bool PossiblePow(const vector<int>& Haybales, double R) {
    double Low = 0, High = 1e9;
    while (RoundOne(Low) < RoundOne(High)) {
        double Mid = Low + (High - Low) / 2;
        int Res = PossibleLoc(Haybales, R, Mid);
        if (Res == 0) return false;
        else if (Res == 3) return true;
        else if (Res == 1) Low = Mid;
        else High = Mid;
    }
    return false;
}

int main() {
    int N;
    double Low = 0, High = 1e9;
    fin >> N;
    vector<int> Haybales(N);
    for (int i = 0; i < N; i++) fin >> Haybales[i];
    sort(all(Haybales));
    while (RoundOne(Low) < RoundOne(High)) {
        double Mid = Low + (High - Low) / 2;
        if (PossiblePow(Haybales, Mid)) High = Mid;
        else Low = Mid;
    }
    assert(RoundOne(Low) == RoundOne(High));
    fout << PrintAns(RoundOne(Low)) << "\n";
    return 0;
}
