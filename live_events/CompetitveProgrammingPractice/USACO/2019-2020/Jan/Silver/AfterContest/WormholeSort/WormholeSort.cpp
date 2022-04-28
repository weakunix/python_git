#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("wormsort.out");
ifstream fin("wormsort.in");

bool SortHoles(const vector<int>& a, const vector<int>& b) {
    return a[2] < b[2];
}

int main() {
    int N, M, CurWeight = 0;
    fin >> N >> M;
    vector<int> CowOrd = {0};
    unordered_set<int> OutPlace, CanBeSorted;
    unordered_map<int, unordered_set<int> > Edges;
    vector<vector<int> > Wormholes;
    for (int i = 1; i <= N; i++) {
        int NewCow;
        fin >> NewCow;
        CowOrd.push_back(NewCow);
        if (NewCow != i) OutPlace.insert(NewCow);
    }
    for (int i = 0; i < M; i++) {
        vector<int> NewHole(3);
        fin >> NewHole[0] >> NewHole[1] >> NewHole[2];
        Wormholes.push_back(NewHole);
    }
    if (OutPlace.size() == 0) {
        fout << "-1\n";
        return 0;
    }
    sort(all(Wormholes), SortHoles);
    while (Wormholes.size() > 0) {
        CurWeight = Wormholes.back().back();
        while (Wormholes.size() > 0 and Wormholes.back().back() == CurWeight) {
            int a, b;
            a = Wormholes.back()[0];
            b = Wormholes.back()[1];
            if (Edges.count(a) == 0) Edges[a] = {b};
            else Edges[a].insert(b);
            if (Edges.count(b) == 0) Edges[b] = {a};
            else Edges[b].insert(a);
            for (int i : Edges[a]) {
                for (int j : Edges[b]) {
                    assert(Edges.count(i) > 0 and Edges.count(j) > 0 and Edges[i].size() > 0 and Edges[j].size() > 0);
                    Edges[a].insert(j);
                    Edges[b].insert(i);
                    Edges[i].insert(b);
                    Edges[j].insert(a);
                    Edges[i].insert(j);
                    Edges[j].insert(i);
                }
            }
            Wormholes.pop_back();
        }
        CanBeSorted.clear();
        for (int i : OutPlace) {
            if (Edges[i].count(CowOrd[i]) > 0) CanBeSorted.insert(i);
        }
        for (int i : CanBeSorted) OutPlace.erase(i);
        if (OutPlace.size() == 0) {
            fout << CurWeight << "\n";
            return 0;
        }
    }
    return 1;
}
