#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    int N, YearNum, CowYear, NewCowYear;
    bool Done = false;
    string Name, RelationName, Year, PrevOrNext, Filler;
    cin >> N;
    unordered_map<string, int> CowMap = {{"Bessie", 0}}, YearMap = {{"Ox", 0}, {"Tiger", 1}, {"Rabbit", 2}, {"Dragon", 3}, {"Snake", 4}, {"Horse", 5}, {"Goat", 6}, {"Monkey", 7}, {"Rooster", 8}, {"Dog", 9}, {"Pig", 10}, {"Rat", 11}};
    for (int i = 0; i < N; i++) {
        cin >> Name >> Filler >> Filler >> PrevOrNext >> Year >> Filler >> Filler >> RelationName;
        if (not Done) {
            YearNum = YearMap[Year];
            CowYear = CowMap[RelationName];
            if (PrevOrNext == "previous") {
                NewCowYear = (CowYear - YearNum) % 12;
                if (NewCowYear <= 0) NewCowYear = 12 + NewCowYear;
                CowMap[Name] = CowYear - NewCowYear;
            }
            else {
                NewCowYear = (YearNum - CowYear) % 12;
                if (NewCowYear <= 0) NewCowYear = 12 + NewCowYear;
                CowMap[Name] = CowYear + NewCowYear;
            }
            if (Name == "Elsie") Done = true;
        }
    }
    cout << abs(CowMap["Elsie"]) << "\n";
    return 0;
}
