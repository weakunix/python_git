#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int GetRoot(const int Node, vector<int>& Parent) {
    if (Parent[Node] < 0) return Node;
    Parent[Node] = GetRoot(Parent[Node], Parent);
    return Parent[Node];
}

bool Merge(int a, int b, vector<int>& Parent) {
    a = GetRoot(a, Parent);
    b = GetRoot(b, Parent);

    if (a == b) return false;

    if (Parent[a] < Parent[b]) swap(a, b);
    Parent[b] += Parent[a];
    Parent[a] = b;

    return true;
}

int Subcase() {
    int N, DepthCount = 0, Ans;
    string Bracket;
    cin >> N >> Bracket;
    Ans = 2 * N;
    vector<int> Parent(2 * N, -1), FirstDepth(N + 1, -1), CurDepth(N + 1);
    for (int i = 0; i < 2 * N; i++) {
        bool IsLeft = (Bracket[i] == '(');

        if (IsLeft) {
            DepthCount++;
            CurDepth[DepthCount] = i;
            if (FirstDepth[DepthCount] == -1) FirstDepth[DepthCount] = i;
        }
        else {
            if (Merge(i, CurDepth[DepthCount], Parent)) Ans--;
            if (Merge(i, FirstDepth[DepthCount], Parent)) Ans--;
            if (DepthCount < N) FirstDepth[DepthCount + 1] = -1;
            DepthCount--;
        }
    }

    return Ans;
}

int main() {
    int T;
    cin >> T;
    
    for (int i = 0; i < T; i++) cout << Subcase() << "\n";

    return 0;
}
