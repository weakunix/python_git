/*
Test inputs

1:
4
1 1 2 3

Test outputs

1:
6
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    //Vars
    int N, PetalSum, HasAvgFlower = 0;
    vector<int> AllFlowers, SubFlowers;

    //Temp vars
    int temp_int;
    
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> temp_int;
        AllFlowers.push_back(temp_int);
    }
    for (int i = 0; i < N; i++) {
        SubFlowers.clear();
        PetalSum = 0;
        for (int k = i; k < N; k++) {
            PetalSum += AllFlowers[k];
            SubFlowers.push_back(AllFlowers[k]);
            if (PetalSum % SubFlowers.size() == 0 and count(SubFlowers.begin(), SubFlowers.end(), PetalSum / SubFlowers.size()) > 0)
                HasAvgFlower++;
        }
    }
    cout << HasAvgFlower << "\n";
    return 0;
}
