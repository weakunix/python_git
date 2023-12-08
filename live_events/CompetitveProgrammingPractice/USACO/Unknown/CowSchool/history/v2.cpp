#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

const int N = 5e4;

int n;
simps arr[N], x = {0, 0};
vector<int> ans;

bool cmp(simps a, simps b) {
    if (a.first < 0 and b.first > 0) return true;
    if (a.first > 0 and b.first < 0) return false;
    if (a.first < 0 and b.first < 0) {
        a.first = -a.first;
        b.first = -b.first;
        swap(a, b);
    }
    return a.first * b.second < a.second * b.first;
}

multiset<simps, decltype(cmp)*> bestpos(cmp), bestneg(cmp);

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        arr[i] = {a, b};
        x.first += a;
        x.second += b;
    }
    sort(arr, arr + n, cmp);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            ll a = arr[j].first - arr[i].first, b = arr[j].second - arr[i].second;
            if (b < 0) bestneg.erase(bestneg.find({-a, -b}));
            else bestpos.erase(bestpos.find({a, b}));
        }
        for (int j = i + 1; j < n; j++) {
            ll a = arr[i].first - arr[j].first, b = arr[i].second - arr[j].second;
            if (b < 0) bestneg.insert({-a, -b});
            else bestpos.insert({a, b});
        }
        x.first -= arr[i].first;
        x.second -= arr[i].second;

        bool works = false;
        if (bestpos.size()) {
            auto it = bestpos.end();
            it--;
            if (cmp(x, *it)) works = true;
        }
        if (bestneg.size()) {
            if (cmp(*bestneg.begin(), x)) works = true;
        }
        if (works) ans.push_back(i + 1);
    }

    cout << ans.size() << "\n";
    for (int i : ans) cout << i << "\n";

	return 0;
}
