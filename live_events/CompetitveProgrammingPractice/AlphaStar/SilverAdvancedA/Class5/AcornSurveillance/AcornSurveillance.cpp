#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, int> piipi;

#define all(v) v.begin(), v.end()

int main() {
    int N, Total = 0, Best = 1e9 + 1, Prev = 0;
    vector<piipi> Events;
    set<int> OnCameras;
    cin >> N;
    vector<int> UniqueTime(N);
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        Events.push_back({{a, 1}, i});
        Events.push_back({{b, -1}, i});
    }
    sort(all(Events));
    for (int i = 0; i < 2 * N; i++) {
        if (OnCameras.size() > 0) {
            Total += Events[i].first.first - Prev;
            if (OnCameras.size() == 1) UniqueTime[*OnCameras.begin()] += Events[i].first.first - Prev;
        }
        if (Events[i].first.second == 1) OnCameras.insert(Events[i].second);
        else OnCameras.erase(Events[i].second);
        Prev = Events[i].first.first;
    }
    for (int i : UniqueTime) Best = min(i, Best);
    cout << Total - Best << "\n";
    return 0;
}
