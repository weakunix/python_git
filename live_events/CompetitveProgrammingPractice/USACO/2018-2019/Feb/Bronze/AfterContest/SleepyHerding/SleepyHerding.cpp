#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("herding.out");
ifstream fin("herding.in");

int main() {
    vector<int> CowLoc(3);
    for (int i = 0; i < 3; i++) fin >> CowLoc[i];
    sort(all(CowLoc));
    if (CowLoc[1] - CowLoc[0] == 2 or CowLoc[2] - CowLoc[1] == 2) fout << "1\n";
    else if (CowLoc[1] == CowLoc[0] + 1 and CowLoc[2] == CowLoc[1] + 1) fout << "0\n";
    else fout << "2\n";
    fout << max(CowLoc[1] - CowLoc[0], CowLoc[2] - CowLoc[1]) - 1 << "\n";
    return 0;
}
