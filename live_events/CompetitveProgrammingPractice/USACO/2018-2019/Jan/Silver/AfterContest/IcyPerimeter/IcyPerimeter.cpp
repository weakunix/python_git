#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("perimeter.out");
ifstream fin("perimeter.in");

void FloodFill(const vector<vector<int> >& Grid, vector<vector<bool> >& Visited, int& Area, int& Perim, const int x, const int y) {
    Visited[y][x] = true;
    Area++;
    if (not Visited[y][x - 1]) FloodFill(Grid, Visited, Area, Perim, x - 1, y);
    else if (Grid[y][x - 1] == 0) Perim++;
    if (not Visited[y][x + 1]) FloodFill(Grid, Visited, Area, Perim, x + 1, y);
    else if (Grid[y][x + 1] == 0) Perim++;
    if (not Visited[y - 1][x]) FloodFill(Grid, Visited, Area, Perim, x, y - 1);
    else if (Grid[y - 1][x] == 0) Perim++;
    if (not Visited[y + 1][x]) FloodFill(Grid, Visited, Area, Perim, x, y + 1);
    else if (Grid[y + 1][x] == 0) Perim++;
    return;
}

int main() {
    int N, Area = 0, Perim = 0;
    fin >> N;
    vector<vector<bool> > Visited(N + 2);
    vector<vector<int> > Grid(N + 2);
    for (int x = 0; x < N + 2; x++) {
        Grid[0].push_back(0);
        Visited[0].push_back(true);
    }
    for (int y = 1; y <= N; y++) {
        Grid[y].push_back(0);
        Visited[y].push_back(true);
        for (int x = 0; x < N; x++) {
            char Cell;
            fin >> Cell;
            if (Cell == '#') {
                Grid[y].push_back(1);
                Visited[y].push_back(false);
            }
            else {
                Grid[y].push_back(0);
                Visited[y].push_back(true);
            }
        }
        Grid[y].push_back(0);
        Visited[y].push_back(true);
    }
    for (int x = 0; x < N + 2; x++) {
        Grid[N + 1].push_back(0);
        Visited[N + 1].push_back(true);
    }
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= N; x++) {
            if (not Visited[y][x]) {
                int CurArea = 0, CurPerim = 0;
                FloodFill(Grid, Visited, CurArea, CurPerim, x, y);
                if (CurArea == Area) Perim = min(CurPerim, Perim);
                else if (CurArea > Area) {
                    Area = CurArea;
                    Perim = CurPerim;
                }
            }
        }
    }
    fout << Area << " " << Perim << "\n";
    return 0;
}
