#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("berries.out");
ifstream fin("berries.in");

int main() {
    int N, K, Best = 0;
    fin >> N >> K;
    vector<int> Trees(N);
    for (int i = 0; i < N; i++) fin >> Trees[i];
    sort(Trees.rbegin(), Trees.rend());
    for (int i = 1; i <= Trees[0]; i++) {
        int Count = 0, Cur = 0;
        vector<int> TreesCopy = Trees;
        for (int j = 0; j < N; j++) {
            if (TreesCopy[j] / i == 0) break;
            Count += TreesCopy[j] / i;
            TreesCopy[j] %= i;
        }
        if (Count >= K / 2) {
            sort(TreesCopy.rbegin(), TreesCopy.rend());
            Count -= K / 2;
            if (Count <= K / 2) Cur = Count * i;
            else Cur = (K / 2) * i;
            for (int j : TreesCopy) {
                if (Count >= K / 2) break;
                Cur += j;
                Count++;
            }
        }
        Best = max(Cur, Best);
    }
    fout << Best << "\n";
    return 0;
}
