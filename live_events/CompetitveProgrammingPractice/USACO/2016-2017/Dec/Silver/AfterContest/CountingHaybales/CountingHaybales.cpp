#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()
#define lb(v, t) lower_bound(all(v), t)
#define ub(v, t) upper_bound(all(v), t)

ofstream fout("haybales.out");
ifstream fin("haybales.in");

int main() {
    int N, Q;
    fin >> N >> Q;
    vector<int> Haybales(N);
    for (int i = 0; i < N; i++) fin >> Haybales[i];
    sort(all(Haybales));
    for (int i = 0; i < Q; i++) {
        int s, e;
        fin >> s >> e;
        fout << ub(Haybales, e) - lb(Haybales, s) << "\n";
    }
    return 0;
}
