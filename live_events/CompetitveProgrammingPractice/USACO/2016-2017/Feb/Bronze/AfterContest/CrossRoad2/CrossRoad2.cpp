/*
Test outputs

1:
1
*/

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

ofstream fout("circlecross.out");
ifstream fin("circlecross.in");

int main() {

    //Vars
    int CrossPairs = 0;
    string CrossPoints;
    unordered_map<char, vector<int> > CrossPointMap;
    vector<vector<char> > CowPairs;

    //Set vars
    for (char c = 'A'; c < 'Z'; c++) {
        for (char d = c + 1; d <= 'Z'; d++)
            CowPairs.push_back({c, d});
    }
    for (char c = 'A'; c <= 'Z'; c++)
        CrossPointMap[c] = {};

    fin >> CrossPoints;
    for (int i = 0; i < CrossPoints.size(); i++)
        CrossPointMap[CrossPoints[i]].push_back(i);
    for (vector<char> v : CowPairs) {
        int p1 = CrossPointMap[v[0]][0], p2 = CrossPointMap[v[0]][1], q1 = CrossPointMap[v[1]][0], q2 = CrossPointMap[v[1]][1];
        if (min(p2, q2) - max(p1, q1) > 0 and !((min(p2, q2) == p2 and max(p1, q1) == p1) or (min(p2, q2) == q2 and max(p1, q1) == q1)))
            CrossPairs++;
    }
    fout << CrossPairs << "\n";
    return 0;
}
