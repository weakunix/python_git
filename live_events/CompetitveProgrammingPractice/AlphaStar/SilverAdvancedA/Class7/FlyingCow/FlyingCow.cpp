#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

int Bfs(const int N) {
    if (N == 1) return 0;
    bool Visited[(int) 1e6 + 1];
    queue<pii> NodeQueue;
    NodeQueue.push({1, 0});
    Visited[1] = true;
    while (not NodeQueue.empty()) {
        int Cur = NodeQueue.front().first, Energy = NodeQueue.front().second;
        if ((Cur - 1 == N or Cur + 1 == N) or 3 * Cur == N) return Energy + 1;
        if (Cur > 1 and not Visited[Cur - 1]) {
            Visited[Cur - 1] = true;
            NodeQueue.push({Cur - 1, Energy + 1});
        }
        if (Cur < 1e6 and not Visited[Cur + 1]) {
            Visited[Cur + 1] = true;
            NodeQueue.push({Cur + 1, Energy + 1});
        }
        if (3 * Cur < 1e6 and not Visited[3 * Cur]) {
            Visited[3 * Cur] = true;
            NodeQueue.push({3 * Cur, Energy + 1});
        }
        NodeQueue.pop();
    }
    return -1;
}

int main() {
    int N;
    cin >> N;
    cout << Bfs(N) << "\n";
    return 0;
}
