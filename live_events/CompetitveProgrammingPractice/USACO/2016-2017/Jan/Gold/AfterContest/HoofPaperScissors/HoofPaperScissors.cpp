#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("hps.out");
ifstream fin("hps.in");

int main() {
    int N, K;
    vector<vector<int> > Hoof, Paper, Scissors;
    fin >> N >> K;
    vector<char> Games(N);
    for (int i = 0; i < N; i++) fin >> Games[i];
    for (int k = 0; k <= K; k++) {
        vector<int> Row(N);
        Hoof.push_back(Row);
        Paper.push_back(Row);
        Scissors.push_back(Row);
        for (int n = 0; n < N; n++) {
            int BestSwitch = 0;
            if (n > 0) {
                Hoof[k][n] = Hoof[k][n - 1];
                Paper[k][n] = Paper[k][n - 1];
                Scissors[k][n] = Scissors[k][n - 1];
                if (k > 0) BestSwitch = max({Hoof[k - 1][n - 1], Paper[k - 1][n - 1], Scissors[k - 1][n - 1]});
            }
            Hoof[k][n] = max(BestSwitch, Hoof[k][n]);
            Paper[k][n] = max(BestSwitch, Paper[k][n]);
            Scissors[k][n] = max(BestSwitch, Scissors[k][n]);
            if (Games[n] == 'H') Hoof[k][n]++;
            else if (Games[n] == 'P') Paper[k][n]++;
            else Scissors[k][n]++;
        }
    }
    fout << max({Hoof[K][N - 1], Paper[K][N - 1], Scissors[K][N - 1]}) << "\n";
    return 0;
}
