#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    int N, K, Ans = 1;
    set<int> Events, NotAllowed;
    map<int, vector<int> > Unfriendly;
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        Events.insert(a);
        Events.insert(b);
        Unfriendly[min(a, b)].push_back(max(a, b));
    }
    for (int i : Events) {
        if (NotAllowed.count(i) > 0) {
            Ans++;
            NotAllowed.clear();
        }
        for (int j : Unfriendly[i]) NotAllowed.insert(j);
    }
    cout << Ans << "\n";
    return 0;
}
