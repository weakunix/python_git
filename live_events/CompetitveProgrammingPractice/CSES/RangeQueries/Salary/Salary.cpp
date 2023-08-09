#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using index_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define ook order_of_key
#define fbo find_by_order

int n, q;
vector<int> arr;
index_set<simps> s;

int main() {
    cin >> n >> q;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        s.insert({arr[i], i});
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        char t;
        cin >> t >> a >> b;
        if (t == '!') {
            a--;
            s.erase({arr[a], a});
            arr[a] = b;
            s.insert({arr[a], a});
            continue;
        }
        cout << s.ook({b, 1e9}) - s.ook({a, -1}) << "\n";
    }
	return 0;
}
