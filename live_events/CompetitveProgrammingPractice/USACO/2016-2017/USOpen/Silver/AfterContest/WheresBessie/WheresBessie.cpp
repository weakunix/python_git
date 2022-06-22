#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;
typedef pair<simps, simps> double_date;

#define fir first.first
#define sec first.second
#define third second.first
#define fourth second.second

ofstream fout("where.out");
ifstream fin("where.in");

int ConnectedCells(const vector<vector<int> >& SubImg, vector<vector<bool> >& Visited, const int Width, const int Height, const int x, const int y) {
    int NodeCount = 1;
    Visited[y][x] = true;
    if (x > 0 and not Visited[y][x - 1]) {
        if (SubImg[y][x - 1] == SubImg[y][x]) NodeCount += ConnectedCells(SubImg, Visited, Width, Height, x - 1, y);
    }
    if (y > 0 and not Visited[y - 1][x]) {
        if (SubImg[y - 1][x] == SubImg[y][x]) NodeCount += ConnectedCells(SubImg, Visited, Width, Height, x, y - 1);
    }
    if (x < Width and not Visited[y][x + 1]) {
        if (SubImg[y][x + 1] == SubImg[y][x]) NodeCount += ConnectedCells(SubImg, Visited, Width, Height, x + 1, y);
    }
    if (y < Height and not Visited[y + 1][x]) {
        if (SubImg[y + 1][x] == SubImg[y][x]) NodeCount += ConnectedCells(SubImg, Visited, Width, Height, x, y + 1);
    }
    return NodeCount;
}

int main() {
    int N, Ans = 0;
    vector<double_date> PsblPcls;
    fin >> N;
    vector<vector<char> > Img(N);
    for (int i = 0; i < N; i++) {
        string Row;
        fin >> Row;
        for (char c : Row) Img[i].push_back(c);
    }
    for (int minx = 0; minx < N; minx++) {
        for (int maxx = minx; maxx < N; maxx++) {
            for (int miny = 0; miny < N; miny++) {
                for (int maxy = miny; maxy < N; maxy++) {
                    int FirstCount = 0, SecondCount = 0, FirstX, FirstY, SecondX, SecondY;
                    char First = '0', Second = '0';
                    bool Psbl = true;
                    vector<vector<int> > SubImg;
                    for (int y = miny; y <= maxy; y++) {
                        if (not Psbl) break;
                        SubImg.push_back({});
                        for (int x = minx; x <= maxx; x++) {
                            char Cur = Img[y][x];
                            if (Cur == First) {
                                FirstCount++;
                                SubImg.back().push_back(0);
                            }
                            else {
                                if (First == '0') {
                                    FirstCount++;
                                    First = Cur;
                                    FirstX = x - minx;
                                    FirstY = y - miny;
                                    SubImg.back().push_back(0);
                                }
                                else {
                                    if (Cur == Second) {
                                        SecondCount++;
                                        SubImg.back().push_back(1);
                                    }
                                    else {
                                        if (Second == '0') {
                                            SecondCount++;
                                            Second = Cur;
                                            SecondX = x - minx;
                                            SecondY = y - miny;
                                            SubImg.back().push_back(1);
                                        }
                                        else {
                                            Psbl = false;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (Psbl and (First != '0' and Second != '0')) {
                        vector<vector<bool> > FirstVisited, SecondVisited;
                        for (int y = miny; y <= maxy; y++) {
                            FirstVisited.push_back({});
                            SecondVisited.push_back({});
                            for (int x = minx; x <= maxx; x++) {
                                FirstVisited.back().push_back(false);
                                SecondVisited.back().push_back(false);
                            }
                        }
                        if ((ConnectedCells(SubImg, FirstVisited, maxx - minx, maxy - miny, FirstX, FirstY) == FirstCount) xor (ConnectedCells(SubImg, SecondVisited, maxx - minx, maxy - miny, SecondX, SecondY) == SecondCount)) PsblPcls.push_back({{minx, miny}, {maxx, maxy}});
                    }
                }
            }
        }
    }
    for (int i = 0; i < PsblPcls.size(); i++) {
        bool Psbl = true;
        const double_date& First = PsblPcls[i];
        for (int j = 0; j < PsblPcls.size(); j++) {
            const double_date& Second = PsblPcls[j];
            if ((((Second.fir <= First.fir) and (Second.sec <= First.sec)) and ((Second.third >= First.third and Second.fourth >= First.fourth))) and i != j) {
                Psbl = false;
                break;
            }
        }
        if (Psbl) Ans++;
    }
    fout << Ans << "\n";
    return 0;
}
