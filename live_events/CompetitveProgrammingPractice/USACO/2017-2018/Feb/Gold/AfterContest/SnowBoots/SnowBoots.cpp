#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

ofstream fout("snowboots.out");
ifstream fin("snowboots.in");

int main() {
    int N, B, MaxRange = 1;
    vector<simps> Tiles;
    map<int, int> RangePoints;
    map<simps, vector<int> > Boots;
    fin >> N >> B;
    vector<int> Result(B);
    for (int i = 0; i < N; i++) {
        int f;
        fin >> f;
        Tiles.push_back({f, i});
    }
    for (int i = 0; i < B; i++) {
        simps s;
        fin >> s.first >> s.second;
        if (Boots.count(s) == 0) Boots[s] = {i};
        else Boots[s].push_back(i);
    }
    sort(all(Tiles));
    for (auto it = Boots.rbegin(); it != Boots.rend(); it++) {
        const simps& CurBoot = it->first;
        assert(Tiles.size() > 0);
        vector<simps> RemovedTiles;
        while (Tiles.back().first > CurBoot.first) {
            int TileLoc = Tiles.back().second;
            assert(TileLoc > 0 and TileLoc < N - 1);
            if (RangePoints.count(TileLoc - 1) > 0 and RangePoints.count(TileLoc + 1) > 0) {
                int b = TileLoc - 1, c = TileLoc + 1;
                assert(RangePoints.count(b) > 0);
                assert(RangePoints.count(c) > 0);
                int a = RangePoints[b], d = RangePoints[c];
                assert(b >= a and d >= c);
                assert(RangePoints.count(a) > 0);
                assert(RangePoints.count(d) > 0);
                RangePoints.erase(b);
                RangePoints.erase(c);
                RangePoints[a] = d;
                RangePoints[d] = a;
                MaxRange = max(d - a + 2, MaxRange);
            }
            else if (RangePoints.count(TileLoc - 1) > 0) {
                int b = TileLoc - 1;
                assert(RangePoints.count(b) > 0);
                int a = RangePoints[b];
                assert(RangePoints.count(a) > 0);
                assert(b >= a);
                RangePoints.erase(b);
                RangePoints[TileLoc] = a;
                RangePoints[a] = TileLoc;
                MaxRange = max(TileLoc - a + 2, MaxRange);
            }
            else if (RangePoints.count(TileLoc + 1) > 0) {
                int a = TileLoc + 1;
                assert(RangePoints.count(a) > 0);
                int b = RangePoints[a];
                assert(RangePoints.count(b) > 0);
                assert(b >= a);
                RangePoints.erase(a);
                RangePoints[TileLoc] = b;
                RangePoints[b] = TileLoc;
                MaxRange = max(b - TileLoc + 2, MaxRange);
            }
            else {
                RangePoints[TileLoc] = TileLoc;
                MaxRange = max(2, MaxRange);
            }
            RemovedTiles.push_back(Tiles.back());
            Tiles.pop_back();
            assert(Tiles.size() > 0);
        }
        if (CurBoot.second >= MaxRange) {
            for (int i : it->second) Result[i] = 1;
        }
    }
    for (int i : Result) fout << i << "\n";
    return 0;
}
