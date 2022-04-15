#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("sleepy.out");
ifstream fin("sleepy.in");

#define all(v) v.begin(), v.end()

int main() {
    int N, Count = 0;
    fin >> N;
    vector<int> CowOrd(N);
    for (int i = 0; i < N; i++) fin >> CowOrd[i];
    while (CowOrd.size() > 0) {
        vector<int> TempCowOrd = CowOrd;
        sort(all(TempCowOrd));
        if (TempCowOrd == CowOrd) {
            fout << Count << "\n";
            return 0;
        }
        Count++;
        CowOrd.erase(CowOrd.begin());
    }
    return 1;
}
