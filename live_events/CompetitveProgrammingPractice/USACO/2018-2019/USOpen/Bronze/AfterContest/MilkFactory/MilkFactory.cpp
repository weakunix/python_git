#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("factory.out");
ifstream fin("factory.in");

int main() {
    int N;
    fin >> N;
    vector<int> OutDeg(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        fin >> a >> b;
        OutDeg[a - 1]++;
    }
    if (count(all(OutDeg), 0) != 1) fout << "-1\n";
    else fout << find(all(OutDeg), 0) - OutDeg.begin() + 1 << "\n";
    return 0;
}
