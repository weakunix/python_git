#include <iostream>
#include <vector>
#include <utility>
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

int n, k, cur = 0;
index_set<int> s;

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) s.insert(i);
    while (not s.empty()) {
        cur = (cur + k) % s.size();
        cout << *s.fbo(cur) << " ";
        s.erase(s.fbo(cur));
    }
	return 0;
}
