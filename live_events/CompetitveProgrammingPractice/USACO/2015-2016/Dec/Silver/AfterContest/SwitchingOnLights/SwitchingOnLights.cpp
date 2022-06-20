#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

typedef pair<int, int> simps;

ofstream fout("lightson.out");
ifstream fin("lightson.in");

int main() {
    int N, M, LightsOn = 1;
    set<simps> NextRooms = {{0, 1}, {1, 0}}, Tested = {{0, 0}};
    map<simps, vector<simps> > TurnOns;
    fin >> N >> M;
    vector<vector<bool> > AreLightsOn(N);
    for (int i = 0; i < M; i++) {
        int x, y, a, b;
        fin >> x >> y >> a >> b;
        x--;
        y--;
        a--;
        b--;
        simps Room = {x, y}, Light = {a, b};
        if (TurnOns.count(Room) == 0) TurnOns[Room] = {Light};
        else TurnOns[Room].push_back(Light);
    }
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) AreLightsOn[y].push_back(x == 0 and y == 0);
    }
    for (const simps& s : TurnOns[make_pair(0, 0)]) {
        if (not AreLightsOn[s.second][s.first]) {
            AreLightsOn[s.second][s.first] = true;
            LightsOn++;
        }
    }
    while (true) {
        int x = -1, y = -1;
        for (auto it = NextRooms.begin(); it != NextRooms.end(); it++) {
            if (AreLightsOn[it->second][it->first]) {
                x = it->first;
                y = it->second;
                break;
            }
        }
        if (x == -1 and y == -1) break;
        NextRooms.erase({x, y});
        Tested.insert({x, y});
        if (x > 0 and Tested.count({x - 1, y}) == 0) NextRooms.insert({x - 1, y});
        if (y > 0 and Tested.count({x, y - 1}) == 0) NextRooms.insert({x, y - 1});
        if (x < N - 1 and Tested.count({x + 1, y}) == 0) NextRooms.insert({x + 1, y});
        if (y < N - 1 and Tested.count({x, y + 1}) == 0) NextRooms.insert({x, y + 1});
        for (const simps& s : TurnOns[make_pair(x, y)]) {
            if (not AreLightsOn[s.second][s.first]) {
                AreLightsOn[s.second][s.first] = true;
                LightsOn++;
            }
        }
    }
    fout << LightsOn << "\n";
    return 0;
}
