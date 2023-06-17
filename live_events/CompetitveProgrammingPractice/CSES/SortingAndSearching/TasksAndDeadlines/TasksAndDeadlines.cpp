#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n;
ll tm = 0, ans = 0;
vector<simps> tasks;

int main() {
    cin >> n;
    tasks.resize(n);
    for (simps& s : tasks) cin >> s.first >> s.second;
    sort(all(tasks));
    for (simps& s : tasks) {
        tm += s.first;
        ans += s.second - tm;
    }
    cout << ans << "\n";
	return 0;
}
