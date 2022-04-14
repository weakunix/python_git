#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

ofstream fout("citystate.out");
ifstream fin("citystate.in");

int main() {
    int N, Total = 0;
    string City, State;
    vector<string> CityState, ReverseCityState;
    map<vector<string>, int> CitiesStates;
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> City >> State;
        CityState = {City.substr(0, 2), State};
        if (CitiesStates.count(CityState) > 0) CitiesStates[CityState]++;
        else CitiesStates[CityState] = 1;
    }
    for (auto it = CitiesStates.begin(); it != CitiesStates.end(); it++) {
        City = it->first[0];
        State = it->first[1];
        if (City != State) {
            CityState = {State, City};
            Total += it->second * CitiesStates[CityState];
        }
    }
    fout << Total / 2 << "\n";
    return 0;
}
