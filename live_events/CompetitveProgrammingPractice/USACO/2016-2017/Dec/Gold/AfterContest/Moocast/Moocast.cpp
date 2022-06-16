#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> simps;

ofstream fout("moocast.out");
ifstream fin("moocast.in");

int Dfs(const vector<vector<int> >& Connections, vector<bool>& Visited, int Cow) {
    int Visits = 1;
    Visited[Cow] = true;
    for (int i : Connections[Cow]) {
        if (not Visited[i]) Visits += Dfs(Connections, Visited, i);
    }
    return Visits;
}

bool IsPossiblePow(const vector<simps>& Cows, int N, int Pow) {
    vector<bool> Visited(N);
    vector<vector<int> > Connections(N);
    for (int a = 0; a < N - 1; a++) {
        for (int b = a + 1; b < N; b++) {
            int XDif = Cows[a].first - Cows[b].first, YDif = Cows[a].second - Cows[b].second;
            if (XDif * XDif + YDif * YDif <= Pow) {
                Connections[a].push_back(b);
                Connections[b].push_back(a);
            }
        }
    }
    return (Dfs(Connections, Visited, 0) == N);
}

int main() {
    int N, Low = 0, High = 2 * 25000 * 25000;
    fin >> N;
    vector<simps> Cows(N);
    for (int i = 0; i < N; i++) fin >> Cows[i].first >> Cows[i].second;
    while (Low < High) {
        int Mid = Low + (High - Low) / 2;
        if (IsPossiblePow(Cows, N, Mid)) High = Mid;
        else Low = Mid + 1;
    }
    assert(Low == High);
    fout << Low << "\n";
    return 0;
}
