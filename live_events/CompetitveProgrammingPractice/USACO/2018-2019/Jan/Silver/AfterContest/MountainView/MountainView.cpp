#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

bool MountSort(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second > b.second;
}

ofstream fout("mountains.out");
ifstream fin("mountains.in");

int main() {
    int N;
    vector<pair<int, int> > Mounts, BaseRanges;
    fin >> N;
    for (int i = 0; i < N; i++) {
        pair<int, int> NewMount;
        fin >> NewMount.first >> NewMount.second;
        Mounts.push_back(NewMount);
    }
    sort(all(Mounts), MountSort);
    for (const pair<int, int>& p : Mounts) {
        pair<int, int> NewRange = {p.first - p.second, p.first + p.second};
        bool Worked = true;
        for (const pair<int, int> q : BaseRanges) {
            if (q.first <= NewRange.first and q.second >= NewRange.second) {
                Worked = false;
                break;
            }
        }
        if (Worked) BaseRanges.push_back(NewRange);
    }
    fout << BaseRanges.size() << "\n";
    return 0;
}
