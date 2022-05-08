#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()

ofstream fout("convention2.out");
ifstream fin("convention2.in");

bool TimeSort(const threesome& a, const threesome& b) {
    return a.second > b.second;
}

int main() {
    int N, CurTime = 0, WorstWait = 0;
    vector<threesome> Times;
    set<threesome> Waiting;
    fin >> N;
    for (int i = 0; i < N; i++) {
        int a, t;
        fin >> a >> t;
        Times.push_back({i, {a, t}});
    }
    sort(all(Times), TimeSort);
    while (Times.size() > 0 or Waiting.size() > 0) {
        while (Times.size() > 0 and Times.back().sec <= CurTime) {
            Waiting.insert(Times.back());
            Times.pop_back();
        }
        if (Waiting.size() == 0) {
            assert(Times.size() > 0);
            CurTime = Times.back().sec;
        }
        else {
            auto NextInLine = Waiting.begin();
            WorstWait = max(CurTime - NextInLine->sec, WorstWait);
            CurTime += NextInLine->third;
            Waiting.erase(NextInLine);
        }
    }
    fout << WorstWait;
    return 0;
}
