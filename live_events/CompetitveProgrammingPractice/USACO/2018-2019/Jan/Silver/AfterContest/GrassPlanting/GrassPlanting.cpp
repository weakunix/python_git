#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("planting.out");
ifstream fin("planting.in");

int main() {
    int N, MaxDeg = 0;
    fin >> N;
    vector<int> Degrees(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        fin >> a >> b;
        Degrees[a - 1]++;
        Degrees[b - 1]++;
    }
    for (int i : Degrees) MaxDeg = max(i, MaxDeg);
    fout << MaxDeg + 1 << "\n";
    return 0;
}
