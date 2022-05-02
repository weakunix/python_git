#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("split.out");
ifstream fin("split.in");

bool YSort(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
}

int MinTwoRect(const vector<pair<int, int> >& Loc, const vector<int>& XCompress, const vector<int>& YCompress) {
    int CurX = -1, LastX = Loc.back().first, MinY = 50000, MaxY = -1;
    long long Best = -1;
    vector<int> RightSideMinY, RightSideMaxY;
    for (auto it = Loc.rbegin(); it != Loc.rend(); it++) {
        if (it == Loc.rbegin()) {
            CurX = it->first;
            RightSideMinY.push_back(YCompress[it->second]);
            RightSideMaxY.push_back(YCompress[it->second]);
        }
        else {
            if (it->first == CurX) {
                RightSideMinY[RightSideMinY.size() - 1] = min(YCompress[it->second], RightSideMinY.back());
                RightSideMaxY[RightSideMaxY.size() - 1] = max(YCompress[it->second], RightSideMaxY.back());
            }
            else {
                CurX = it->first;
                RightSideMinY.push_back(min(YCompress[it->second], RightSideMinY.back()));
                RightSideMaxY.push_back(max(YCompress[it->second], RightSideMaxY.back()));
            }
        }
    }
    reverse(all(RightSideMinY));
    reverse(all(RightSideMaxY));
    for (int i = 0; i < Loc.size(); i++) {
        int ThisX = p.first;
        const pair<int, int>& p = Loc[i];
        if (ThisX == LastX) break;
        assert(i != Loc.size() - 1);
        int NextX = Loc[i + 1].first;
        MinY = min(CompressY[p.second], MinY);
        MaxY = max(CompressX[p.second], MaxX);
        if (ThisX != NextX) {
            Best = min(
        }
    }
    if (Best == -1) return 0;
    return Best;
}

int main() {
    int N, CompressCoord = -1, PrevCompress = -1;
    vector<pair<int, int> > Loc;
    vector<int> XCompress, YCompress;
    fin >> N;
    for (int i = 0; i < N; i++) {
        pair<int, int> NewLoc;
        fin >> NewLoc.first >> NewLoc.second;
        Loc.push_back(NewLoc);
    }
    sort(all(Loc), YSort);
    for (pair<int, int>& p : Loc) {
        if (p.second == PrevCompress) {
            YCompress.push_back(p.second);
            p.second = CompressCoord;
        }
        else {
            CompressCoord++;
            YCompress.push_back(p.second);
            PrevCompress = p.second;
            p.second = CompressCoord;
        }
    }
    sort(all(Loc));
    CompressCoord = -1;
    PrevCompress = -1;
    for (pair<int, int>& p : Loc) {
        if (p.first == PrevCompress) {
            XCompress.push_back(p.first);
            p.first = CompressCoord;
        }
        else {
            CompressCoord++;
            XCompress.push_back(p.first);
            PrevCompress = p.first;
            p.first = CompressCoord;
        }
    }
    MinTwoRect(Loc, XCompress, YCompress);
    return 0;
}
