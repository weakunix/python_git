/*
Test outputs

1:
10
*/

#include <fstream>
#include <vector>
#include <map>

using namespace std;

ofstream fout("mowing.out");
ifstream fin("mowing.in");

int main() {

    //Vars
    int N, MaxX = -1, MoveCount = 1;
    vector<int> CurrentLoc = {0, 0};
    vector<char> Moves;
    map<vector<int>, int> VisitedPoints = {{{0, 0}, 1}};

    //Temp vars
    char temp_char;
    int temp_int;

    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> temp_char >> temp_int;
        for (int k = 0; k < temp_int; k++)
            Moves.push_back(temp_char);
    }
    for (char c : Moves) {
        MoveCount += 1;
        if (c == 'N')
            CurrentLoc[0] += 1;
        else if (c == 'S')
            CurrentLoc[0] -= 1;
        else if (c == 'E')
            CurrentLoc[1] += 1;
        else
            CurrentLoc[1] -= 1;
        temp_int = VisitedPoints[CurrentLoc];
        if (temp_int > 0 and (MaxX == -1 or MaxX > MoveCount - temp_int))
            MaxX = MoveCount - temp_int;
        VisitedPoints[CurrentLoc] = MoveCount;
    }
    fout << MaxX << "\n";
    return 0;
}
