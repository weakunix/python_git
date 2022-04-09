/*
Test outputs

1:
whatthefun
*/

#include <fstream>
#include <string>

using namespace std;

ofstream fout("censor.out");
ifstream fin("censor.in");

int main() {

    //Vars
    string S, T, NewS = "";
    int LenT;
    
    fin >> S >> T;
    LenT = T.size();
    for (int i = 0; i < S.size(); i++) {
        NewS += S[i];
        if (NewS.size() >= LenT and NewS.substr(NewS.size() - LenT, LenT) == T) {
            NewS.resize(NewS.size() - LenT);
        }
    }
    fout << NewS << "\n";
    return 0;
}
