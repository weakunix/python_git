/*
Test outputs

1:
4
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("diamond.out");
ifstream fin("diamond.in");

int main() {

    //Vars
    int N, K, CurDiamonds, MaxDiamonds = 0;
    vector<int> Diamonds;

    //Temp vars
    int temp_int;

    fin >> N >> K;
    for (int i = 0; i < N; i++) {
        fin >> temp_int;
        Diamonds.push_back(temp_int);
    }
    sort(Diamonds.begin(), Diamonds.end());
    for (int i = 0; i < Diamonds.size(); i++) {
        CurDiamonds = 1;
        for (int k = i + 1; k < Diamonds.size(); k++) {
            if (Diamonds[k] - Diamonds[i] > K)
                break;
            CurDiamonds += 1;
        }
        MaxDiamonds = max(CurDiamonds, MaxDiamonds);
    }
    fout << MaxDiamonds << "\n";
    return 0;
}
