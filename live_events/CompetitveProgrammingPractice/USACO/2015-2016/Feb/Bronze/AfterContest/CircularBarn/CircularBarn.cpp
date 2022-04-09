/*
Test outputs

1:
48
*/

#include <fstream>
#include <vector>

using namespace std;

ofstream fout("cbarn.out");
ifstream fin("cbarn.in");

int main() {

    //Vars
    int n, TotalSteps, BestTotalSteps = 0;
    vector<int> RoomCount;

    //Temp vars
    int temp_int;

    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> temp_int;
        RoomCount.push_back(temp_int);
    }
    for (int StartingPoint = 0; StartingPoint < n; StartingPoint++) {
        TotalSteps = 0;
        for (int i = 0; i < n; i++) {
            temp_int = (i + StartingPoint) % n;
            TotalSteps += RoomCount[temp_int] * i;
        }
        if (BestTotalSteps == 0 or TotalSteps < BestTotalSteps)
            BestTotalSteps = TotalSteps;
    }
    fout << BestTotalSteps << "\n";
    return 0;
}
