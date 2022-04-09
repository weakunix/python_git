/*
Test outputs

1:
5
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("speeding.out");
ifstream fin("speeding.in");

int main() {

    //Vars
    int N, M, NextDist, CurLim, CurActual, NewSpeeding;
    int MaxSpeeding = 0;
    vector<vector<int> > SpeedLim, SpeedActual;


    //Temp vars
    int temp_int;
    vector<int> temp_vect_int;

    fin >> N >> M;
    for (int i = 0; i < N; i++) {
        temp_vect_int.clear();
        fin >> temp_int;
        if (i == 0) {
            temp_vect_int.push_back(0);
        }
        else {
            temp_vect_int.push_back(SpeedLim[SpeedLim.size() - 1][0] + NextDist);
        }
        NextDist = temp_int;
        fin >> temp_int;
        temp_vect_int.push_back(temp_int);
        SpeedLim.push_back(temp_vect_int);
    }
    for (int i = 0; i < M; i++) {
        temp_vect_int.clear();
        fin >> temp_int;
        if (i == 0) {
            temp_vect_int.push_back(0);
        }
        else {
            temp_vect_int.push_back(SpeedActual[SpeedActual.size() - 1][0] + NextDist);
        }
        NextDist = temp_int;
        fin >> temp_int;
        temp_vect_int.push_back(temp_int);
        SpeedActual.push_back(temp_vect_int);
    }
    while (not SpeedLim.empty() and not SpeedActual.empty()) {
        if (SpeedLim[0][0] == SpeedActual[0][0]) {
            CurLim = SpeedLim[0][1];
            CurActual = SpeedActual[0][1];
            SpeedLim.erase(SpeedLim.begin());
            SpeedActual.erase(SpeedActual.begin());
        }
        else if (SpeedLim[0][0] < SpeedActual[0][0]) {
            CurLim = SpeedLim[0][1];
            SpeedLim.erase(SpeedLim.begin());
        }
        else {
            CurActual = SpeedActual[0][1];
            SpeedActual.erase(SpeedActual.begin());
        }
        NewSpeeding = max(CurActual - CurLim, 0);
        if (NewSpeeding > MaxSpeeding)
            MaxSpeeding = NewSpeeding;
    }
    if (SpeedLim.empty()) {
        while (not SpeedActual.empty()) {
            CurActual = SpeedActual[0][1];
            SpeedActual.erase(SpeedActual.begin());
            NewSpeeding = max(CurActual - CurLim, 0);
            if (NewSpeeding > MaxSpeeding)
                MaxSpeeding = NewSpeeding;
        }
    }
    else {
        while (not SpeedLim.empty()) {
            CurLim = SpeedLim[0][1];
            SpeedLim.erase(SpeedLim.begin());
            NewSpeeding = max(CurActual - CurLim, 0);
            if (NewSpeeding > MaxSpeeding)
                MaxSpeeding = NewSpeeding;
        }
    }
    fout << MaxSpeeding << "\n";
    return 0;
}
