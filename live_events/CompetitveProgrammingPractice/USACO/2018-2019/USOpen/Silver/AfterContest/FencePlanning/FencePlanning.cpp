#include <fstream>
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

ofstream fout("fenceplan.out");
ifstream fin("fenceplan.in");

double_date Dfs(const vector<vector<int> >& Connections, const vector<simps>& Cows, vector<bool>& Visited, int Cow) {
    double_date CurFence = {Cows[Cow], Cows[Cow]};
    Visited[Cow] = true;
    for (int i : Connections[Cow]) {
        if (not Visited[i]) {
            double_date NewFence = Dfs(Connections, Cows, Visited, i);
            CurFence.fir = min(NewFence.fir, CurFence.fir);
            CurFence.sec = min(NewFence.sec, CurFence.sec);
            CurFence.third = max(NewFence.third, CurFence.third);
            CurFence.fourth = max(NewFence.fourth, CurFence.fourth);
        }
    }
    return CurFence;
}

int main() {
    int N, M, Ans = 4e8;
    fin >> N >> M;
    vector<bool> Visited(N);
    vector<simps> Cows(N);
    vector<vector<int> > Connections(N);
    for (int i = 0; i < N; i++) fin >> Cows[i].first >> Cows[i].second;
    for (int i = 0; i < M; i++) {
        int a, b;
        fin >> a >> b;
        a--;
        b--;
        Connections[a].push_back(b);
        Connections[b].push_back(a);
    }
    for (int i = 0; i < N; i++) {
        if (not Visited[i]) {
            double_date CurFence = Dfs(Connections, Cows, Visited, i);
            Ans = min(2 * (CurFence.third - CurFence.fir + CurFence.fourth - CurFence.sec), Ans);
        }
    }
    fout << Ans << "\n";
    return 0;
}
