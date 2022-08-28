#include <iostream>
#include <cstdio>
#include <vector>
#include <deque>
#include <algorithm>
#include <cassert>

using namespace std;

int N;
vector<int> Dirty;

#define all(v) v.begin(), v.end()

bool IsPossiblePrefix(const int End) {
    vector<int> Smallest;

    for (int i = 0; i < End; i++) Smallest.push_back(Dirty[i]);

    sort(all(Smallest));

    int CurSmall = 0;
    deque<int> TopDq;
    deque<vector<int> > StackDq;

    for (int i = 0; i < End; i++) {
        int Dish = Dirty[i], Idx = upper_bound(all(TopDq), Dish) - TopDq.begin();

        if (Idx == TopDq.size()) {
            TopDq.push_back(Dish);
            StackDq.push_back({Dish});
        }
        else {
            TopDq[Idx] = Dish;
            StackDq[Idx].push_back(Dish);
        }

        while ((CurSmall < End and not StackDq.empty()) and StackDq[0].back() == Smallest[CurSmall]) {
            CurSmall++;
            StackDq[0].pop_back();
            if (StackDq[0].size() == 0) {
                StackDq.pop_front();
                TopDq.pop_front();
                continue;
            }
            TopDq[0] = StackDq[0].back();
        }

        assert(TopDq.size() == StackDq.size());

        if (CurSmall == End) return true;
    }

    return false;
}

int main() {
    freopen("dishes.in", "r", stdin);
    freopen("dishes.out", "w", stdout);

    cin >> N;
    Dirty.resize(N);
    for (int i = 0; i < N; i++) cin >> Dirty[i];

    int Low = 1, High = N;
    while (Low < High) {
        int Mid = Low + (High - Low + 1) / 2;

        if (IsPossiblePrefix(Mid)) Low = Mid;
        else High = Mid - 1;
    }

    assert(Low == High);

    cout << Low << "\n";

    return 0;
}
