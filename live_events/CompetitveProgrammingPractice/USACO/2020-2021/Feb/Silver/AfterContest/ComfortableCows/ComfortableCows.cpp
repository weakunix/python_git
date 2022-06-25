#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

//#include <cstdio>

using namespace std;

void AddNewVals(vector<vector<int> >& Farm, vector<vector<bool> >& Visited, queue<int>& XVals, queue<int>& YVals, const int x, const int y) {
    if ((x >= 0 and x <= 2000) and (y >= 0 and y <= 2000)) {
        Farm[y][x]++;
        if (Visited[y][x] and Farm[y][x] == 3) {
            if (not Visited[y][x - 1]) {
                Visited[y][x - 1] = true;
                XVals.push(x - 1);
                YVals.push(y);
            }
            if (not Visited[y - 1][x]) {
                Visited[y - 1][x] = true;
                XVals.push(x);
                YVals.push(y - 1);
            }
            if (not Visited[y][x + 1]) {
                Visited[y][x + 1] = true;
                XVals.push(x + 1);
                YVals.push(y);
            }
            if (not Visited[y + 1][x]) {
                Visited[y + 1][x] = true;
                XVals.push(x);
                YVals.push(y + 1);
            }
        }
    }
    return;
}

void FloodFill(vector<vector<int> >& Farm, vector<vector<bool> >& Visited, int& CowCount, const int FirstX, const int FirstY) {
    queue<int> XVals, YVals;
    Visited[FirstY][FirstX] = true;
    XVals.push(FirstX);
    YVals.push(FirstY);
    while (XVals.size() > 0) {
        int x = XVals.front(), y = YVals.front();
        CowCount++;
        Farm[y][x]--;
        AddNewVals(Farm, Visited, XVals, YVals, x, y);
        AddNewVals(Farm, Visited, XVals, YVals, x - 1, y);
        AddNewVals(Farm, Visited, XVals, YVals, x, y - 1);
        AddNewVals(Farm, Visited, XVals, YVals, x + 1, y);
        AddNewVals(Farm, Visited, XVals, YVals, x, y + 1);
        XVals.pop();
        YVals.pop();
    }
    return;
}

int main() {
    //freopen("test.txt", "r", stdin);
    int N, CowCount = 0;
    vector<vector<int> > Farm;
    vector<vector<bool> > Visited;
    for (int i = 0; i < 2001; i++) {
        vector<int> Row(2001);
        Farm.push_back(Row);
    }
    for (int i = 0; i < 2001; i++) {
        vector<bool> Row(2001);
        Visited.push_back(Row);
    }
    cin >> N;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        x += 500;
        y += 500;
        if (not Visited[y][x]) FloodFill(Farm, Visited, CowCount, x, y);
        CowCount--;
        cout << CowCount << "\n";
    }
    return 0;
}
