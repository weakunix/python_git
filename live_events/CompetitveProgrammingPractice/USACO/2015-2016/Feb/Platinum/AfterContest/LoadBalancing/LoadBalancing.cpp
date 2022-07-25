#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

ofstream fout("balancing.out");
ifstream fin("balancing.in");

bool SortReverseY(const simps& a, const simps& b) {
    return a.second > b.second;
}

int GetBestUpDownDiv(const set<simps>& Above, const set<simps>& Below, int Best) {
    int Low = 0, High = 1e6 / 2;
    while (Low < High) {
        int Mid = Low + (High - Low + 1) / 2, XDiv = 2 * Mid, a = distance(Above.lower_bound({XDiv, 0}), Above.end()), b = distance(Below.lower_bound({XDiv, 0}), Below.end()), c = Below.size() - b, d = Above.size() - a;
        Best = min(max({a, b, c, d}), Best);
        a = max(a, b);
        b = max(c, d);
        if (a == b) break;
        else if (a < b) High = Mid - 1;
        else Low = Mid + 1;
    }
    return Best;
}

int main() {
    int N, Best;
    set<simps> Above, Below;
    vector<simps> RemainingCows;
    fin >> N;
    Best = N;
    for (int i = 0; i < N; i++) {
        int x, y;
        fin >> x >> y;
        Above.insert({x, y});
        RemainingCows.push_back({x, y});
    }
    sort(all(RemainingCows), SortReverseY);
    while (RemainingCows.size() > 0) {
        int y = RemainingCows.back().second;
        while (RemainingCows.size() > 0 and RemainingCows.back().second == y) {
            Below.insert(RemainingCows.back());
            Above.erase(RemainingCows.back());
            RemainingCows.pop_back();
        }
        Best = GetBestUpDownDiv(Above, Below, Best);
    }
    fout << Best << "\n";
    return 0;
}
