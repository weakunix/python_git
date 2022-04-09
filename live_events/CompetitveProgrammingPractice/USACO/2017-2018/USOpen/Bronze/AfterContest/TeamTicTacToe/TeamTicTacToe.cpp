/*
Test outputs

1:
0
2
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("tttt.out");
ifstream fin("tttt.in");

int main() {

    //Vars
    vector<char> Grid, OneWin;
    vector<vector<char> > TwoWin;
    vector<vector<int> > Tests = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

    //Temp vars
    char temp_char;
    vector<char> temp_vect_char;

    for (int i = 0; i < 9; i++) {
        fin >> temp_char;
        Grid.push_back(temp_char);
    }
    for (vector<int> i : Tests) {
        temp_vect_char = {Grid[i[0]], Grid[i[1]], Grid[i[2]]};
        if (count(temp_vect_char.begin(), temp_vect_char.end(), temp_vect_char[0]) == 3) {
            if (count(OneWin.begin(), OneWin.end(), temp_vect_char[0]) == 0)
                OneWin.push_back(temp_vect_char[0]);
        }
        else if (count(temp_vect_char.begin(), temp_vect_char.end(), temp_vect_char[0]) == 2 or temp_vect_char[1] == temp_vect_char[2]) {
            if (temp_vect_char[0] != temp_vect_char[1])
                temp_vect_char = {temp_vect_char[0], temp_vect_char[1]};
            else
                temp_vect_char = {temp_vect_char[0], temp_vect_char[2]};
            sort(temp_vect_char.begin(), temp_vect_char.end());
            if (count(TwoWin.begin(), TwoWin.end(), temp_vect_char) == 0)
                TwoWin.push_back(temp_vect_char);
        }
    }
    fout << OneWin.size() << "\n" << TwoWin.size() << "\n";
    return 0;
}
