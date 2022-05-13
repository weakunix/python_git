#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

ofstream fout("cardgame.out");
ifstream fin("cardgame.in");

int main() {
    int N, Wins = 0;
    vector<int> FirstRnd, SecondRnd, Bessie;
    set<int> Elsie;
    fin >> N;
    for (int i = 0; i < N / 2; i++) {
        int CurCard;
        fin >> CurCard;
        FirstRnd.push_back(CurCard);
        Elsie.insert(CurCard);
    }
    sort(FirstRnd.rbegin(), FirstRnd.rend());
    for (int i = 0; i < N / 2; i++) {
        int CurCard;
        fin >> CurCard;
        SecondRnd.push_back(CurCard);
        Elsie.insert(CurCard);
    }
    sort(SecondRnd.begin(), SecondRnd.end());
    for (int i = 1; i <= 2 * N; i++) {
        if (Elsie.count(i) == 0) Bessie.push_back(i);
    }
    for (int i : FirstRnd) {
        if (Bessie.back() > i) {
            Bessie.pop_back();
            Wins++;
        }
        else {
            fout << "";
        }
    }
    reverse(Bessie.begin(), Bessie.end());
    for (int i : SecondRnd) {
        if (Bessie.back() < i) {
            Bessie.pop_back();
            Wins++;
        }
    }
    fout << Wins << "\n";
    return 0;
}
