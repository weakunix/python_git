#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n, k;
ll curans = 0;
simps curmed;
set<simps> rng;
vector<int> arr;

void getfirst() {
    for (int i = 0; i < k; i++) rng.insert({arr[i], i});
    auto it = rng.begin();
    for (int i = 0; i < (k - 1) / 2; i++) it++;
    curmed = *it;
    for (int i = 0; i < k; i++) curans += abs(arr[i] - curmed.first);
    return;
}

int main() {
    cin >> n >> k;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    if (k == 1) {
        for (int i = 0; i < n; i++) cout << "0 ";
        cout << "\n";
        return 0;
    }
    getfirst();
    cout << curans << " ";
    for (int i = k; i < n; i++) {
        simps rem = {arr[i - k], i - k}, add = {arr[i], i};
        auto it = rng.find(curmed);
        if (k % 2 == 0) {
            if (rem <= curmed) it++;
        }
        else {
            if (rem >= curmed) {
                it--;
                curans += curmed.first - it->first;
            }
        }
        curmed = *it;
        curans -= abs(curmed.first - rem.first);
        rng.erase(rem);
        rng.insert(add);
        curans += abs(curmed.first - add.first);
        it = rng.find(curmed);
        if (k % 2 == 0) {
            if (add < curmed) it--;
        }
        else {
            if (add > curmed) {
                it++;
                curans -= (it->first - curmed.first);
            }
        }
        curmed = *it;
        cout << curans << " ";
    }
    cout << "\n";
	return 0;
}
