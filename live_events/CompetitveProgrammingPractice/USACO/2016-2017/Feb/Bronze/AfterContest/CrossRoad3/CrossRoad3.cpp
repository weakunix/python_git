#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("cowqueue.out");
ifstream fin("cowqueue.in");

bool CowSort(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
}

int main() {
    int N, CurrentTime = 0;
    fin >> N;
    vector<vector<int> > Cows(N);
    for (int i = 0; i < N; i++) {
        vector<int> CurCow(2);
        fin >> CurCow[0] >> CurCow[1];
        Cows[i] = CurCow;
    }
    sort(all(Cows), CowSort);
    for (vector<int> v : Cows) {
        CurrentTime = max(v[0], CurrentTime) + v[1];
    }
    fout << CurrentTime << "\n";
    return 0;
}
