/*
Test outputs

1:
0
10
2
*/

#include <fstream>
#include <vector>

using namespace std;

ofstream fout("mixmilk.out");
ifstream fin("mixmilk.in");

int main() {

    //Vars
    vector<int> MaxCap, CurCap;
    int CurInd, NextInd;
    
    //Temp vars
    int inpt;

    for (int i = 0; i < 3; i++) {
        fin >> inpt;
        MaxCap.push_back(inpt);
        fin >> inpt;
        CurCap.push_back(inpt);
    }
    for (int i = 0; i < 100; i++) {
        CurInd = i % 3;
        NextInd = (CurInd + 1) % 3;
        if (CurCap[NextInd] + CurCap[CurInd] <=  MaxCap[NextInd]) {
            CurCap[NextInd] = CurCap[NextInd] + CurCap[CurInd];
            CurCap[CurInd] = 0;
        }
        else {
            CurCap[CurInd] = CurCap[CurInd] - (MaxCap[NextInd] - CurCap[NextInd]);
            CurCap[NextInd] = MaxCap[NextInd];
        }
    }
    for (int i : CurCap) {
        fout << i << "\n";
    }
    return 0;
}
