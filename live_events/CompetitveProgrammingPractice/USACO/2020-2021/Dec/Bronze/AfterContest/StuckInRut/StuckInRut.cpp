/*
Test inputs

1:
6
E 3 5
N 5 3
E 4 6
E 10 4
N 11 2
N 8 1

Test outputs

1:
5
3
Infinity
Infinity
2
5
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool SortNorthCows(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
}

bool SortEastCows(const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
}

int main() {
    
    //Vars
    int N;
    map<int, vector<int> > CowMap;
    map<vector<int>, int> GrassEaten;
    vector<vector<int> > East, North;

    //Temp vars
    vector<int> temp_vect_int, to_erase;
    int temp_int;
    char temp_char;

    cin >> N;
    for (int i = 0; i < N; i++) {
        temp_vect_int.clear();
        cin >> temp_char >> temp_int;
        temp_vect_int.push_back(temp_int);
        cin >> temp_int;
        temp_vect_int.push_back(temp_int);
        CowMap[i] = temp_vect_int;
        GrassEaten[temp_vect_int] = -1;
        if (temp_char == 'N')
            North.push_back(temp_vect_int);
        else
            East.push_back(temp_vect_int);
    }
    sort(North.begin(), North.end(), SortNorthCows);
    sort(East.begin(), East.end(), SortEastCows);
    for (vector<int> e : East) {
        to_erase.clear();
        for (int i = 0; i < North.size(); i++) {
            vector<int> n = North[i];
            if (e[0] < n[0] and e[1] > n[1]) {
                if (n[0] - e[0] < e[1] - n[1]) {
                    GrassEaten[n] = e[1] - n[1];
                    to_erase.push_back(i);
                }
                else if (n[0] - e[0] > e[1] - n[1]) {
                    GrassEaten[e] = n[0] - e[0];
                    break;
                }
            }
        }
        for (int i = 0; i < to_erase.size(); i++) 
            North.erase(North.begin() + to_erase[i] - i);
    }
    for (int i = 0; i < N; i++) {
        temp_int = GrassEaten[CowMap[i]];
        if (temp_int == -1)
            cout << "Infinity\n";
        else
            cout << temp_int << "\n";
    }
    return 0;
}
