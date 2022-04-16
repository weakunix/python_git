#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("hoofball.out");
ifstream fin("hoofball.in");

int main() {
    int N, Count = 0;
    fin >> N;
    vector<int> CowLoc(N), Dir(N), Cur;
    for (int i = 0; i < N; i++) fin >> CowLoc[i];
    sort(all(CowLoc));
    for (int i = 0; i < N; i++) {
        if (i == 0) Dir[0] = 1;
        else if (i == N - 1) Dir[N - 1] = -1;
        else {
            if (CowLoc[i] - CowLoc[i - 1] <= CowLoc[i + 1] - CowLoc[i]) Dir[i] = -1;
            else Dir[i] = 1;
        }
    }
    for (int i : Dir) {
        if (i == 1) {
            if (count(all(Cur), -1) > 0) {
                Count++;
                Cur.clear();
            }
        }
        else {
            if (count(all(Cur), -1) > 0 and count(all(Cur), 1) > 1) {
                Count++;
                Cur.clear();
            }
        }
        Cur.push_back(i);
    }
    if (Cur.size() > 0) Count++;
    fout << Count << "\n";
    return 0;
}
