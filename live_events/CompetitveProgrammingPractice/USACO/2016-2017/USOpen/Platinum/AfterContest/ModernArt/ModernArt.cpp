#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

ofstream fout("art.out");
ifstream fin("art.in");

int main() {
    int N;
    fin >> N;
    unordered_set<int> Possible, TotalColors;
    const vector<int> Default = {1001, 1001, -1, -1};
    vector<vector<int> > Rect = {Default}, FinishArt, Pre;
    for (int i = 1; i <= N * N; i++) {
        Possible.insert(i);
        Rect.push_back({1001, 1001, -1, -1});
    }
    for (int y = 0; y <= N + 1; y++) {
        vector<int> NewRow(N + 2);
        Pre.push_back(NewRow);
    }
    for (int y = 0; y <= N; y++) {
        vector<int> NewRow(N + 1);
        if (y != 0) {
            for (int x = 1; x <= N; x++) {
                int Color;
                fin >> Color;
                NewRow[x] = Color;
                if (Color != 0) {
                    Rect[Color][0] = min(x, Rect[Color][0]);
                    Rect[Color][1] = min(y, Rect[Color][1]);
                    Rect[Color][2] = max(x, Rect[Color][2]);
                    Rect[Color][3] = max(y, Rect[Color][3]);
                    TotalColors.insert(Color);
                }
            }
        }
        FinishArt.push_back(NewRow);
    }
    if (TotalColors.size() == 0) {
        fout << "0\n";
        return 0;
    }
    if (TotalColors.size() == 1) {
        fout << N * N - 1 << "\n";
        return 0;
    }
    for (vector<int> v : Rect) {
        if (v != Default) {
            int minx = v[0], miny = v[1], maxx = v[2], maxy = v[3];
            Pre[miny][minx]++;
            Pre[miny][maxx + 1]--;
            Pre[maxy + 1][minx]--;
            Pre[maxy + 1][maxx + 1]++;
        }
    }
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= N; x++) {
            Pre[y][x] = Pre[y][x] + Pre[y][x - 1] + Pre[y - 1][x] - Pre[y - 1][x - 1];
            if (Pre[y][x] >= 2) Possible.erase(FinishArt[y][x]);
        }
    }
    fout << Possible.size() << "\n";
    return 0;
}
