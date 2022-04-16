#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

ofstream fout("art.out");
ifstream fin("art.in");

int main() {
    int N, Color;
    string Line;
    vector<vector<int> > Art;
    set<int> NotPossible;
    unordered_map<int, vector<int> > Rects; //minx, miny, maxx, maxy
    fin >> N;
    for (int y = 0; y < N; y++) {
        fin >> Line;
        Art.push_back({});
        for (int x = 0; x < N; x++) {
            Color = Line[x] - '0';
            Art[y].push_back(Color);
            if (Color != 0) {
                if (Rects.count(Color) == 0) {
                    Rects[Color] = {x, y, x, y};
                }
                else {
                    Rects[Color][3] = y;
                    Rects[Color][0] = min(x, Rects[Color][0]);
                    Rects[Color][2] = max(x, Rects[Color][2]);
                }
            }
        }
    }
    for (auto it = Rects.begin(); it != Rects.end(); it++) {
        for (int y = it->second[1]; y <= it->second[3]; y++) {
            for (int x = it->second[0]; x <= it->second[2]; x++) {
                if (Art[y][x] != it->first) NotPossible.insert(Art[y][x]);
            }
        }
    }
    fout << Rects.size() - NotPossible.size() << "\n";
    return 0;
}
