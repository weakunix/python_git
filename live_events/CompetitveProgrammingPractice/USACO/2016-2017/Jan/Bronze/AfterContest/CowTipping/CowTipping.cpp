#include <fstream>
#include <string>
#include <vector>

using namespace std;

ofstream fout("cowtip.out");
ifstream fin("cowtip.in");

void FlipCows(vector<vector<int> >& CowStatus, const int& MaxX, const int& MaxY) {
    for (int y = 0; y <= MaxY; y++) {
        for (int x = 0; x <= MaxX; x++) {
            if (CowStatus[y][x] == 1) CowStatus[y][x] = 0;
            else CowStatus[y][x] = 1;
        }
    }
    return;
}

int main() {
    int N, Flips = 0;
    string Row;
    fin >> N;
    int x = 0, y = N;
    vector<vector<int> > CowStatus(N);
    for (int i = 0; i < N; i++) {
        fin >> Row;
        for (char c : Row) CowStatus[i].push_back(c - '0');
    }
    while (x > 0 or y > 0) {
        x--;
        if (x == -1) {
            y--;
            x = N - 1;
        }
        if (CowStatus[y][x] == 1) {
            Flips++;
            FlipCows(CowStatus, x, y);
        }
    }
    fout << Flips << "\n";
    return 0;
}
