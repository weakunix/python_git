/*
Test outputs

1:
10 13
8 12
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

ofstream fout("traffic.out");
ifstream fin("traffic.in");

int main() {

    //Vars
    int N;
    vector<int> Range = {0, 1000};
    vector<int> StartingRange;
    vector<vector<int> > Sensors;
    map<string, int> SensorTypeConv = {{"none", 0}, {"on", 1}, {"off", -1}};

    //Temp vars
    vector<int> temp_vect_int;
    int temp_int;
    string temp_str;

    fin >> N;
    for (int i = 0; i < N; i++) {
        temp_vect_int.clear();
        fin >> temp_str;
        temp_vect_int.push_back(SensorTypeConv[temp_str]);
        fin >> temp_int;
        temp_vect_int.push_back(temp_int);
        fin >> temp_int;
        temp_vect_int.push_back(temp_int);
        Sensors.push_back(temp_vect_int);
    }
    for (vector<int> i : Sensors) {
        if (i[0] == 0) {
            Range[0] = max(Range[0], i[1]);
            Range[1] = min(Range[1], i[2]);
        }
        else if (i[0] == 1) {
            Range[0] = max(Range[0] + i[1], 0);
            Range[1] = max(Range[1] + i[2], 0);
        }
        else {
            Range[0] = max(Range[0] - i[2], 0);
            Range[1] = max(Range[1] - i[1], 0);
        }
    }
    StartingRange = Range;
    for (int i = 1; i <= N; i++) {
        temp_vect_int = Sensors[N - i];
        if (temp_vect_int[0] == 0) {
            StartingRange[0] = max(StartingRange[0], temp_vect_int[1]);
            StartingRange[1] = min(StartingRange[1], temp_vect_int[2]);
        }
        else if (temp_vect_int[0] == -1) {
            StartingRange[0] = max(StartingRange[0] + temp_vect_int[1], 0);
            StartingRange[1] = max(StartingRange[1] + temp_vect_int[2], 0);
        }
        else {
            StartingRange[0] = max(StartingRange[0] - temp_vect_int[2], 0);
            StartingRange[1] = max(StartingRange[1] - temp_vect_int[1], 0);
        }
    }
    fout << StartingRange[0] << " " << StartingRange[1] << "\n" << Range[0] << " " << Range[1] << "\n";
    return 0;
}
