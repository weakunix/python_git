#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

ofstream fout("notlast.out");
ifstream fin("notlast.in");

vector<string> FindMinMilkCows(const unordered_map<string, int>& MilkLog) {
    int MinMilk = -1;
    vector<string> MinMilkCows;
    for (auto it = MilkLog.begin(); it != MilkLog.end(); it++) {
        if (it->second < MinMilk or MinMilk == -1) {
            MinMilk = it->second;
            MinMilkCows = {it->first};
        }
        else if (it->second == MinMilk) MinMilkCows.push_back(it->first);
    }
    return MinMilkCows;
}

int main() {
    int N, MilkProduced;
    string Name;
    vector<string> MinMilkCows;
    unordered_map<string, int> MilkLog = {{"Bessie", 0}, {"Elsie", 0}, {"Daisy", 0}, {"Gertie", 0}, {"Annabelle", 0}, {"Maggie", 0}, {"Henrietta", 0}};
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> Name >> MilkProduced;
        MilkLog[Name] += MilkProduced;
    }
    MinMilkCows = FindMinMilkCows(MilkLog);
    for (string s : MinMilkCows) MilkLog.erase(s);
    MinMilkCows = FindMinMilkCows(MilkLog);
    if (MinMilkCows.size() == 1) fout << MinMilkCows[0] << "\n";
    else fout << "Tie\n";
    return 0;
}
