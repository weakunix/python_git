#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> H = {0}, G = {0}, J = {0};
    for (int i = 0; i < N; i++) {
        int Id;
        cin >> Id;
        H.push_back(H.back());
        G.push_back(G.back());
        J.push_back(J.back());
        if (Id == 1) H.back()++;
        else if (Id == 2) G.back()++;
        else J.back()++;
    }
    for (int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        cout << H[b] - H[a] << " " << G[b] - G[a] << " " << J[b] - J[a] << "\n";
    }
    return 0;
}
