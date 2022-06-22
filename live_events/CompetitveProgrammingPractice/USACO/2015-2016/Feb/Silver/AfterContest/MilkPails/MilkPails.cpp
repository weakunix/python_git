#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("pails.out");
ifstream fin("pails.in");

int FloodFill(vector<vector<bool> > Visited, const int X, const int Y, const int K, const int M, const int x, const int y, const int k) {
    if (y == 13)
        fout << "";
    int Best = abs(M - (x + y));
    Visited[y][x] = true;
    if (k < K) {
        vector<int> XVals = {X, x, 0, x}, YVals = {y, Y, y, 0};
        if (x + y <= X) {
            XVals.push_back(x + y);
            YVals.push_back(0);
        }
        else {
            XVals.push_back(X);
            YVals.push_back(x + y - X);
        }
        if (x + y <= Y) {
            XVals.push_back(0);
            YVals.push_back(x + y);
        }
        else {
            XVals.push_back(x + y - Y);
            YVals.push_back(Y);
        }
        for (int i = 0; i < 6; i++) {
            int CurX = XVals[i], CurY = YVals[i];
            if (not Visited[CurY][CurX]) Best = min(FloodFill(Visited, X, Y, K, M, CurX, CurY, k + 1), Best);
        }
    }
    return Best;
}

int main() {
    int X, Y, K, M;
    vector<vector<bool> > Visited(101);
    fin >> X >> Y >> K >> M;
    for (int y = 0; y < 101; y++) {
        for (int x = 0; x < 101; x++) Visited[y].push_back(false);
    }
    fout << FloodFill(Visited, X, Y, K, M, 0, 0, 0) << "\n";
    return 0;
}
