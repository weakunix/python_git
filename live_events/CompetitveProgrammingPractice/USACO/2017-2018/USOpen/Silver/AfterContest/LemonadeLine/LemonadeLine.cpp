#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("lemonade.out");
ifstream fin("lemonade.in");

int main() {
    int N, CowsInLine = 0;
    fin >> N;
    vector<int> Cows(N);
    for (int i = 0; i < N; i++) fin >> Cows[i];
    sort(all(Cows));
    while (Cows.size() > 0) {
        if (Cows.back() < CowsInLine) break;
        CowsInLine++;
        Cows.pop_back();
    }
    fout << CowsInLine << "\n";
    return 0;
}
