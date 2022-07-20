#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, int> piipi;

#define rall(v) v.rbegin(), v.rend()

int main() {
    int N, Time = 0, Ans = 0;
    vector<piipi> Cows;
    map<int, pii> Waiting;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a, t;
        cin >> a >> t;
        Cows.push_back({{a, t}, i});
    }
    sort(rall(Cows));
    while (Cows.size() > 0) {
        if (Waiting.size() == 0 and Cows.back().first.first > Time) Time = Cows.back().first.first;
        while (Cows.size() > 0 and Cows.back().first.first <= Time) {
            Waiting[Cows.back().second] = Cows.back().first;
            Cows.pop_back();
        }
        int a = Waiting.begin()->second.first, t = Waiting.begin()->second.second;
        Ans = max(Time - a, Ans);
        Time += t;
        Waiting.erase(Waiting.begin()->first);
    }
    cout << Ans << "\n";
    return 0;
}
