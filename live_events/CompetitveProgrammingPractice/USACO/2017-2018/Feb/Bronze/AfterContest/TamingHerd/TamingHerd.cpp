#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("taming.out");
ifstream fin("taming.in");

int main() {
    int N, BreakMin;
    fin >> N;
    vector<int> BreakLog(N);
    for (int i = 0; i < N; i++) fin >> BreakLog[i];
    for (int i = N - 1; i > 0; i--) {
        if (BreakLog[i] > 0) {
            if (BreakLog[i - 1] != -1 and BreakLog[i - 1] != BreakLog[i] - 1) {
                fout << "-1\n";
                return 0;
            }
            BreakLog[i - 1] = BreakLog[i] - 1;
        }
    }
    if (BreakLog[0] > 0) {
        fout << "-1\n";
        return 0;
    }
    BreakLog[0] = 0;
    BreakMin = count(all(BreakLog), 0);
    fout << BreakMin << " " << BreakMin + count(all(BreakLog), -1) << "\n";
    return 0;
}
