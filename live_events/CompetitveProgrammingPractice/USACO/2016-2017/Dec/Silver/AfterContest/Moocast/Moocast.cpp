#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;
typedef pair<simps, int> threesome;

#define fir first.first
#define sec first.second

ofstream fout("moocast.out");
ifstream fin("moocast.in");

int Dfs(const vector<vector<int> >& Tree, vector<bool>& Visited, int Node) {
    int Visits = 1;
    Visited[Node] = true;
    for (int i : Tree[Node]) {
        if (not Visited[i]) Visits += Dfs(Tree, Visited, i);
    }
    return Visits;
}

int main() {
    int N, Ans = 0;
    fin >> N;
    vector<threesome> Cows(N);
    vector<vector<int> > Connections(N);
    for (int i = 0; i < N; i++) fin >> Cows[i].fir >> Cows[i].sec >> Cows[i].second;
    for (int a = 0; a < N; a++) {
        for (int b = 0; b < N; b++) {
            if (a != b) {
                int Dist = (Cows[a].fir - Cows[b].fir) * (Cows[a].fir - Cows[b].fir) + (Cows[a].sec - Cows[b].sec) * (Cows[a].sec - Cows[b].sec);
                if (Dist <= Cows[a].second * Cows[a].second) Connections[a].push_back(b);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        vector<bool> Visited(N);
        Ans = max(Dfs(Connections, Visited, i), Ans);
    }
    fout << Ans << "\n";
    return 0;
}
