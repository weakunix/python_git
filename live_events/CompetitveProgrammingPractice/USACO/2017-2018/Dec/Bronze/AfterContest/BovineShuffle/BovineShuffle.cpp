/*
Test outputs

1:
1234567
5555555
2222222
3333333
4444444
*/

#include <fstream>
#include <vector>
#include <map>

using namespace std;

ofstream fout("shuffle.out");
ifstream fin("shuffle.in");

int main() {

    //Vars
    int N;
    vector<string> FinalLoc;
    vector<int> Shuffle;


    //Temp vars
    int temp_int;
    string temp_str;

    FinalLoc.push_back("");
    Shuffle.push_back(0);
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> temp_int;
        Shuffle.push_back(temp_int);
    }
    for (int i = 0; i < N; i++) {
        fin >> temp_str;
        FinalLoc.push_back(temp_str);
    }
    for (int i = 1; i <= N; i++) {
        temp_int = i;
        for (int k = 0; k < 3; k++) {
            temp_int = Shuffle[temp_int];
        }
        fout << FinalLoc[temp_int] << "\n";
    }
    return 0;
}
