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
simps curmed;
vector<int> arr;
set<simps> s;

void getfirstmed() {
    auto it = s.begin();
    for (int i = 0; i < (k - 1) / 2; i++) it++;
    curmed = *it;
}

int main() {
    cin >> n >> k;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    if (k == 1) {
        for (int i : arr) cout << i << " ";
        cout << "\n";
        return 0;
    }
    for (int i = 0; i < k; i++) s.insert({arr[i], i});
    getfirstmed();
    cout << curmed.first << " ";
    for (int i = k; i < n; i++) {
        simps rem = {arr[i - k], i - k}, add = {arr[i], i};
        auto it = s.find(curmed);
        if (n % 2 == 0) {
            if (rem <= curmed) it++;
        }
        else {
            if (rem >= curmed) it--;
        }
        curmed = *it;
        s.erase(rem);
        s.insert(add);
        it = s.find(curmed);
        if (n % 2 == 0) {
            if (add < curmed) it--;
        }
        else {
            if (add > curmed) it++;
        }
        curmed = *it;
        cout << curmed.first << " ";
    }
    cout << "\n";
    return 0;
}
