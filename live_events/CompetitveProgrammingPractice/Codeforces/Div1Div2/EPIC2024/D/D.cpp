#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

int t;
vector<int> arr;

bool cmp(int a, int b) {
    if (arr[a] == arr[b]) return a > b;
    return arr[a] < arr[b];
}

void subcase() {
    arr.clear();

    int n;
    vector<int> ord;
    map<int, int> cnt;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        cnt[cur]++;
    }

    for (auto& u : cnt) arr.pb(u.second);
    
    for (int i = 0; i < arr.size(); i++) ord.pb(i);
    sort(all(ord), cmp);

    set<int> curvals;
    for (int i = 0; i < arr.size(); i++) {
        bool works = true;

        curvals.insert(ord[i]);

        int a = 0;
        queue<int> done;
        for (int j : curvals) {
            a += arr[j];
            while (done.size() and done.front() < a) {
                done.pop();
                a++;
            }
            if (a > j) {
                works = false;
                break;
            }
            done.push(j);
        }

        if (not works) curvals.erase(ord[i]);
    }

    cout << arr.size() - curvals.size() << "\n";


	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
