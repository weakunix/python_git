#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("div7.out");
ifstream fin("div7.in");

int main() {
    int N, Longest = 0;
    vector<int> DivSeven = {0};
    fin >> N;
    for (int i = 0; i < N; i++) {
        int Cow;
        fin >> Cow;
        DivSeven.push_back((DivSeven.back() + Cow) % 7);
    }
    for (int i = 0; i < 7; i++) {
        int First = -1, Cur = -1;
        for (int k = 0; k <= N; k++) {
            if (DivSeven[k] == i) {
                if (First == -1) First = k;
                Cur = k;
            }
        }
        if (First != Cur) Longest = max(Cur - First, Longest);
    }
    fout << Longest << "\n";
    return 0;
}
