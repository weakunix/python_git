#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

int N, D;
vector<int> Ans, BessieOp, ElsieOp, EndPies;

bool BessieComp(const int a, const int b) {
    return BessieOp[a] > BessieOp[b];
}

bool ElsieComp(const int a, const int b) {
    return ElsieOp[a] > ElsieOp[b];
}

multiset<int, decltype(ElsieComp)*> BessiePies(ElsieComp);
multiset<int, decltype(BessieComp)*> ElsiePies(BessieComp);

void BfsPie() {
    queue<simps> NodeQueue;
    for (int i : EndPies) NodeQueue.push({i, 1});
    while (not NodeQueue.empty()) {
        int Cur = NodeQueue.front().first, Dist = NodeQueue.front().second;
        NodeQueue.pop();
        if (Cur < N) {
            vector<int> Remove;
            for (auto it = ElsiePies.lower_bound(Cur); it != ElsiePies.end(); it++) {
                if (BessieOp[*it] + D < BessieOp[Cur]) break;
                Remove.push_back(*it);
            }
            for (int i : Remove) {
                NodeQueue.push({i, Dist + 1});
                ElsiePies.erase(i);
            }
        }
        else {
            vector<int> Remove;
            for (auto it = BessiePies.lower_bound(Cur); it != BessiePies.end(); it++) {
                if (ElsieOp[*it] + D < ElsieOp[Cur]) break;
                Remove.push_back(*it);
            }
            for (int i : Remove) {
                NodeQueue.push({i, Dist + 1});
                BessiePies.erase(i);
                Ans[i] = Dist + 1;
            }
        }
    }
    return;
}

int main() {
    freopen("piepie.in", "r", stdin);
    freopen("piepie.out", "w", stdout);
    cin >> N >> D;
    for (int i = 0; i < N; i++) {
        int b, e;
        cin >> b >> e;
        BessieOp.push_back(b);
        ElsieOp.push_back(e);
        if (e == 0) {
            EndPies.push_back(i);
            Ans.push_back(1);
        }
        else {
            BessiePies.insert(i);
            Ans.push_back(-1);
        }
    }
    for (int i = N; i < 2 * N; i++) {
        int b, e;
        cin >> b >> e;
        BessieOp.push_back(b);
        ElsieOp.push_back(e);
        if (b == 0) EndPies.push_back(i);
        else ElsiePies.insert(i);
    }
    BfsPie();
    for (int i : Ans) cout << i << "\n";
    return 0;
}
