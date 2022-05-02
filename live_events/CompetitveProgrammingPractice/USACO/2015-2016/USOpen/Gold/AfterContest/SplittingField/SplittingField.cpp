#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("split.out");
ifstream fin("split.in");

long long MinTwoRect(const vector<pair<int, int> >& Loc) {
    int CurX = -1, FirstX = Loc[0].first, LastX = Loc.back().first, MinY = 1000000001, MaxY = -1, Count = -1;
    long long Best = -1;
    vector<int> RightSideMinY, RightSideMaxY;
    for (auto it = Loc.rbegin(); it != Loc.rend(); it++) {
        if (it == Loc.rbegin()) {
            CurX = it->first;
            RightSideMinY.push_back(it->second);
            RightSideMaxY.push_back(it->second);
        }
        else {
            if (it->first == CurX) {
                RightSideMinY[RightSideMinY.size() - 1] = min(it->second, RightSideMinY.back());
                RightSideMaxY[RightSideMaxY.size() - 1] = max(it->second, RightSideMaxY.back());
            }
            else {
                CurX = it->first;
                RightSideMinY.push_back(min(it->second, RightSideMinY.back()));
                RightSideMaxY.push_back(max(it->second, RightSideMaxY.back()));
            }
        }
    }
    reverse(all(RightSideMinY));
    reverse(all(RightSideMaxY));
    for (int i = 0; i < Loc.size(); i++) {
        const pair<int, int>& p = Loc[i];
        int ThisX = p.first;
        if (ThisX == LastX) break;
        assert(i != Loc.size() - 1);
        int NextX = Loc[i + 1].first;
        MinY = min(p.second, MinY);
        MaxY = max(p.second, MaxY);
        if (ThisX != NextX) {
            Count++;
            long long a = ThisX - FirstX, b = MaxY - MinY, c = LastX - NextX, d = RightSideMaxY[Count + 1] - RightSideMinY[Count + 1], NewArea = a * b + c * d;
            assert(NewArea >= 0);
            if (Best == -1) Best = NewArea;
            else Best = min(NewArea, Best);
        }
    }
    return Best;
}

int main() {
    int N;
    long long Original, Cur;
    vector<pair<int, int> > Loc;
    fin >> N;
    for (int i = 0; i < N; i++) {
        pair<int, int> NewLoc;
        fin >> NewLoc.first >> NewLoc.second;
        Loc.push_back(NewLoc);
    }
    sort(all(Loc));
    Original = (Loc.back().first - Loc[0].first);
    Cur = MinTwoRect(Loc);
    for (pair<int, int>& p : Loc) {
        int Temp = p.first;
        p.first = p.second;
        p.second = Temp;
    }
    sort(all(Loc));
    Original *= (Loc.back().first - Loc[0].first);
    Cur = min(MinTwoRect(Loc), Cur);
    if (Cur == -1) fout << "0\n";
    else fout << Original -  Cur << "\n";
    return 0;
}
