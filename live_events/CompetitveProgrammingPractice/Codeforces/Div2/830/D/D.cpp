#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

int main() {
    int q;
    set<int> s;
    map<int, int> kmex;
    map<int, vector<int>> invkmex;
    cin >> q;
    s.insert(0);
    for (int i = 0; i < q; i++) {
        char c;
        int v;
        cin >> c >> v;
        if (c == '+') {
            s.insert(v);
            invkmex[v].push_back(v);
            for (int j : invkmex[v]) {
                int val = j;
                while (s.count(j) > 0) val += j;
                kmex[j] = val;
                invkmex[val].push_back(j);
            }
        }
        else {
            cout << kmex[v] << "\n";
        }
    }
    return 0;
}
