#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("highcard.out");
ifstream fin("highcard.in");

int main() {
    int N, Prev = -1, NumOfCards, Wins = 0;
    fin >> N;
    vector<int> Cards(N);
    for (int i = 0; i < N; i++) fin >> Cards[i];
    sort(all(Cards));
    for (auto it = Cards.rbegin(); it != Cards.rend(); it++) {
        int CurCard = *it;
        if (Prev == -1) NumOfCards = 2 * N - CurCard;
        else NumOfCards += Prev - CurCard - 1;
        Prev = CurCard;
        if (NumOfCards > 0) {
            NumOfCards--;
            Wins++;
        }
    }
    fout << Wins << "\n";
    return 0;
}
