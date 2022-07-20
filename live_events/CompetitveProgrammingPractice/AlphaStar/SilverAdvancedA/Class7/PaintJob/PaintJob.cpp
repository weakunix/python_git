#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

int Bfs(const int A, const int B, const int P, const vector<int>& Buckets) {
    vector<bool> Visited(P);
    queue<pii> NodeQueue;
    NodeQueue.push({A, 0});
    Visited[A] = true;
    while (not NodeQueue.empty()) {
        int Cur = NodeQueue.front().first, Count = NodeQueue.front().second;
        if (Cur == B) return Count;
        for (int i : Buckets) {
            int New = (Cur * i) % P;
            if (not Visited[New]) {
                Visited[New] = true;
                NodeQueue.push({New, Count + 1});
            }
        }
        NodeQueue.pop();
    }
    return -1;
}

int main() {
    int A, B, N, P;
    cin >> A >> B >> N >> P;
    vector<int> Buckets(N);
    for (int i = 0; i < N; i++) cin >> Buckets[i];
    A %= P;
    B %= P;
    cout << Bfs(A, B, P, Buckets) << "\n";
    return 0;
}
