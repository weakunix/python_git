/*
Test outputs

1:
2
*/

#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

ofstream fout("triangles.out");
ifstream fin("triangles.in");

int main() {

    //Vars
    int N, MaxArea = 0;
    map<int, vector<int> > YVals, XVals; //YVals = y values for given x, XVals = x values for given y
    vector<vector<int> > Points;

    //Temp vars
    int temp_int;
    vector<int> temp_vect_int;
    
    fin >> N;
    for (int i = 0; i < N; i++) {
        temp_vect_int.clear();
        fin >> temp_int;
        temp_vect_int.push_back(temp_int);
        fin >> temp_int;
        temp_vect_int.push_back(temp_int);
        Points.push_back(temp_vect_int);
        if (YVals.count(temp_vect_int[0]) == 0)
            YVals[temp_vect_int[0]] = {temp_vect_int[1], temp_vect_int[1]};
        else if (YVals[temp_vect_int[0]][0] > temp_vect_int[1])
            YVals[temp_vect_int[0]][0] = temp_vect_int[1];
        else if (YVals[temp_vect_int[0]][1] < temp_vect_int[1])
            YVals[temp_vect_int[0]][1] = temp_vect_int[1];
        if (XVals.count(temp_vect_int[1]) == 0)
            XVals[temp_vect_int[1]] = {temp_vect_int[0], temp_vect_int[0]};
        else if (XVals[temp_vect_int[1]][0] > temp_vect_int[0])
            XVals[temp_vect_int[1]][0] = temp_vect_int[0];
        else if (XVals[temp_vect_int[1]][1] < temp_vect_int[0])
            XVals[temp_vect_int[1]][1] = temp_vect_int[0];
    }
    for (vector<int> v : Points) 
        MaxArea = max(max(YVals[v[0]][1] - v[1], v[1] - YVals[v[0]][0]) * max(XVals[v[1]][1] - v[0], v[0] - XVals[v[1]][0]), MaxArea);
    fout << MaxArea << "\n";
    return 0;
}
