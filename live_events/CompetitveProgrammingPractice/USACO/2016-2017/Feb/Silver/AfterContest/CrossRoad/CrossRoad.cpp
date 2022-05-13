#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

ofstream fout("helpcross.out");
ifstream fin("helpcross.in");

int main() {
    int C, N, Pairs = 0;
    multiset<int> InLine;
    fin >> C >> N;
    vector<int> Chickens(C);
    vector<simps> Cows(N);
    for (int i = 0; i < C; i++) fin >> Chickens[i];
    sort(all(Chickens));
    for (int i = 0; i < N; i++) fin >> Cows[i].first >> Cows[i].second;
    sort(Cows.rbegin(), Cows.rend());
    for (int i : Chickens) {
        while (Cows.size() > 0 and Cows.back().first <= i) {
            InLine.insert(Cows.back().second);
            Cows.pop_back();
        }
        while (InLine.size() > 0) {
            if (*InLine.begin() < i) InLine.erase(InLine.begin());
            else {
                Pairs++;
                InLine.erase(InLine.begin());
                break;
            }
        }
    }
    fout << Pairs << "\n";
    return 0;
}
