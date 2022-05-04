#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("sort.out");
ifstream fin("sort.in");

int main() {
    int N, MinPasses = 0;
    unordered_map<int, vector<int> > FinalIndexes;
    fin >> N;
    vector<int> Arr(N), SortedArr;
    for (int i = 0; i < N; i++) fin >> Arr[i];
    SortedArr = Arr;
    sort(all(SortedArr));
    for (int i = 0; i < N; i++) {
        if (FinalIndexes.count(SortedArr[i]) == 0) FinalIndexes[SortedArr[i]] = {i};
        else FinalIndexes[SortedArr[i]].push_back(i);
    }
    for (int i = 0; i < N; i++) {
        int a = FinalIndexes[Arr[i]][0];
        FinalIndexes[Arr[i]].erase(FinalIndexes[Arr[i]].begin());
        Arr[i] = a;
    }
    for (int i = 0; i < N; i++) {
        if (Arr[i] < i) MinPasses = max(i - Arr[i], MinPasses);
    }
    fout << MinPasses + 1 << "\n";
    return 0;
}
