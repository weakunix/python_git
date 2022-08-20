#include <fstream>
#include <vector>

using namespace std;

ofstream fout("help.out");
ifstream fin("help.in");

int main() {
    int N, Ans = 0;
    const int ModVal = 1e9 + 7;
    vector<int> Segments, PowTwo = {1};
    fin >> N;
    vector<int> Pfx(2 * N + 1);
    for (int i = 0; i < N; i++) {
        PowTwo.push_back((PowTwo.back() * 2) % ModVal);
        int a, b;
        fin >> a >> b;
        Segments.push_back(a);
        Pfx[a]++;
        Pfx[b]--;
    }
    for (int i = 1; i <= 2 * N; i++) Pfx[i] += Pfx[i - 1];
    for (int i : Segments) Ans = (Ans + PowTwo[N - 1 - Pfx[i - 1]]) % ModVal;
    fout << Ans << "\n";
    return 0;
}
