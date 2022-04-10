#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("lineup.out");
ifstream fin("lineup.in");

bool CheckArr(const vector<vector<string> >& Conds, const vector<string>& Arr) {
    for (vector<string> v : Conds) {
        int dif = find(Arr.begin(), Arr.end(), v[0]) - find(Arr.begin(), Arr.end(), v[1]);
        if (dif != 1 and dif != -1) return false;
    }
    return true;
}

int main() {
    int N;
    fin >> N;
    vector<string> Cows = {"Bessie", "Buttercup", "Belinda", "Beatrice", "Bella", "Blue", "Betsy", "Sue"};
    sort(Cows.begin(), Cows.end());
    vector<vector<string> > Conds(N);
    for (int i = 0; i < N; i++) {
        string temp_str;
        vector<string> Cond(2);
        fin >> Cond[0];
        for (int k = 0; k < 4; k++) fin >> temp_str;
        fin >> Cond[1];
        Conds[i] = Cond;
    }
    while (true) {
        if (CheckArr(Conds, Cows)) {
            for (string s : Cows) fout << s << "\n";
            return 0;
        }
        next_permutation(Cows.begin(), Cows.end());
    }
}
