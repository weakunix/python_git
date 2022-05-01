#include <iostream>
#include <vector>
#include <utility>
#include <unordered_set>
#include <map>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

bool EastSort(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
}

int Dfs(const vector<vector<int> >& Tree, int Node) {
    int Total = 1;
    for (int i : Tree[Node]) Total += Dfs(Tree, i);
    return Total;
}

int main() {
    int N;
    vector<pair<int, int> > East, North;
    unordered_set<int> Stopped;
    map<pair<int, int>, int> CowID;
    cin >> N;
    vector<vector<int> > Blames(N);
    for (int i = 0; i < N; i++) {
        char NewDir;
        pair<int, int> NewLoc;
        cin >> NewDir >> NewLoc.first >> NewLoc.second;
        CowID[NewLoc] = i;
        if (NewDir == 'E') East.push_back(NewLoc);
        else North.push_back(NewLoc);
    }
    sort(all(East), EastSort);
    sort(all(North));
    for (const pair<int, int>& e : East) {
        for (int i = 0; i < North.size(); i++) {
            if (Stopped.count(i) == 0) {
                const pair<int, int>& n = North[i];
                if (n.second <= e.second and e.first <= n.first) {
                    int x = n.first, y = e.second, ndist = y - n.second, edist = x - e.first;
                    if (ndist < edist) {
                        Blames[CowID[n]].push_back(CowID[e]);
                        break;
                    }
                    if (ndist > edist) {
                        Blames[CowID[e]].push_back(CowID[n]);
                        Stopped.insert(i);
                    }
                }
            }
        }
    }
    for (int i = 0; i < N; i++) cout << Dfs(Blames, i) - 1 << "\n";
    return 0;
}
