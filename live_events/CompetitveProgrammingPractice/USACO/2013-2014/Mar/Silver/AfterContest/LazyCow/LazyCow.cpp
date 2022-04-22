#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("lazy.out");
ifstream fin("lazy.in");

int main() {
    int N, K, Best = 0;
    vector<vector<int> > PreG;
    fin >> N >> K;
    for (int y = 0; y <= N; y++) {
        vector<int> NewPre(N + 1);
        if (y > 0) {
            for (int x = 1; x <= N; x++) {
                int g;
                fin >> g;
                NewPre[x] = g + NewPre[x - 1];
            }
        }
        PreG.push_back(NewPre);
    }
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= N; x++) {
            int Cur = PreG[y][min(x + K, N)] - PreG[y][max(x - K, 1) - 1];
            for (int i = 1; i <= K; i++) {
                if (y + i > N and y - i < 1) break;
                if (y + i <= N) Cur += PreG[y + i][min(x + K - i, N)] - PreG[y + i][max(x - K + i, 1) - 1];
                if (y - i >= 1) Cur += PreG[y - i][min(x + K - i, N)] - PreG[y - i][max(x - K + i, 1) - 1];

            }
            Best = max(Cur, Best);
        }
    }
    fout << Best << "\n";
    return 0;
}
