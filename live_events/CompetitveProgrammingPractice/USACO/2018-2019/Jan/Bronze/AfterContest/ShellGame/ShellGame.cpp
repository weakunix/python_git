/*
Test outputs

1:
2
*/

#include <fstream>
#include <vector>
#include <map>

using namespace std;

ofstream fout("shell.out");
ifstream fin("shell.in");

int main() {

    //Vars
    int N, a, b, g, CorrectGuesses, ShellLoc;
    int BestOutcome = 0;
    vector<pair<int, int> > Swaps;
    vector<int> Guesses;

    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> a >> b >> g;
        Swaps.push_back(make_pair(a, b));
        Guesses.push_back(g);
    }
    for (int i = 1; i <= 3; i++) {
        ShellLoc = i;
        CorrectGuesses = 0;
        for (int k = 0; k < N; k++) {
            if (ShellLoc == Swaps[k].first)
                ShellLoc = Swaps[k].second;
            else if (ShellLoc == Swaps[k].second)
                ShellLoc = Swaps[k].first;
            if (ShellLoc == Guesses[k])
                CorrectGuesses += 1;
        }
        if (CorrectGuesses > BestOutcome)
            BestOutcome = CorrectGuesses;
    }
    fout << BestOutcome << "\n";
    return 0;
}
