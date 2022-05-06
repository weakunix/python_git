#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

ofstream fout("pairup.out");
ifstream fin("pairup.in");

int main() {
    int N, MaxTime = 0, Left = 0;
    vector<simps> Cows;
    fin >> N;
    int Right = N - 1;
    for (int i = 0; i < N; i++) {
        int n, t;
        fin >> n >> t;
        Cows.push_back({t, n});
    }
    sort(all(Cows));
    while (Left < Right) {
        simps& LeftElem = Cows[Left];
        simps& RightElem = Cows[Right];
        int PairCount = min(LeftElem.second, RightElem.second);
        MaxTime = max(LeftElem.first + RightElem.first, MaxTime);
        LeftElem.second -= PairCount;
        RightElem.second -= PairCount;
        if (LeftElem.second == 0) Left++;
        if (RightElem.second == 0) Right--;
    }
    if (Left == Right) MaxTime = max(2 * Cows[Left].first, MaxTime);
    fout << MaxTime << "\n";
    return 0;
}
