#include <fstream>
#include <vector>

using namespace std;

ofstream fout("paintbarn.out");
ifstream fin("paintbarn.in");

int main() {
    int N, K, Total = 0;
    vector<vector<int> > Changes, Pre;
    for (int i = 0; i <= 1001; i++) {
        vector<int> NewRow(1002);
        Changes.push_back(NewRow);
        Pre.push_back(NewRow);
    }
    fin >> N >> K;
    for (int i = 0; i < N; i++) {
        int a, b, c, d;
        fin >> a >> b >> c >> d;
        a++;
        b++;
        c++;
        d++;
        Changes[b][a]++;
        Changes[b][c]--;
        Changes[d][a]--;
        Changes[d][c]++;
    }
    for (int y = 1; y <= 1001; y++) {
        for (int x = 1; x <= 1001; x++) {
            Pre[y][x] = Changes[y][x] + Pre[y - 1][x] + Pre[y][x - 1] - Pre[y - 1][x - 1];
            if (Pre[y][x] == K) Total++;
        }
    }
    fout << Total << "\n";
    return 0;
}
