/*
Test outputs

1:
1
*/

#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

ofstream fout("cownomics.out");
ifstream fin("cownomics.in");

int main() {

    //Vars
    int N, M, PossibleGenomes = 0;
    bool IsPossible;
    vector<string> SpotGenomes, PlainGenomes;
    set<char> Spots, Plains;
    
    //Temp vars
    string temp_str;

    fin >> N >> M;
    for (int i = 0; i < N; i++) {
        fin >> temp_str;
        SpotGenomes.push_back(temp_str);
    }
    for (int i = 0; i < N; i++) {
        fin >> temp_str;
        PlainGenomes.push_back(temp_str);
    }
    for (int i = 0; i < M; i++) {
        Spots.clear();
        Plains.clear();
        IsPossible = true;
        for (string s : SpotGenomes)
            Spots.insert(s[i]);
        for (string s : PlainGenomes)
            Plains.insert(s[i]);
        for (char c : Spots) {
            if (count(Plains.begin(), Plains.end(), c) > 0) {
                IsPossible = false;
                break;
            }
        }
        if (IsPossible)
            PossibleGenomes++;
    }
    fout << PossibleGenomes << "\n";
    return 0;
}
