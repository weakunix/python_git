#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

ofstream fout("rental.out");
ifstream fin("rental.in");

#define all(v) v.begin(), v.end()

bool PerGalSort(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
}

pair<long long, pair<int, int> > MilkCow(int MilkRemain, const vector<pair<int, int> >& Milk) {
    long long Profit = 0;
    int PopCount = 0, RemoveFromLast = 0;
    while (MilkRemain > 0 and PopCount < Milk.size()) {
        long long a = Milk[Milk.size() - 1 - PopCount].first, b = Milk[Milk.size() - 1 - PopCount].second;
        if (MilkRemain >= a) {
            Profit += a * b;
            MilkRemain -= a;
            PopCount++;
        }
        else {
            Profit += MilkRemain * b;
            RemoveFromLast = MilkRemain;
            MilkRemain = 0;
        }
    }
    return {Profit, {PopCount, RemoveFromLast}};
}

void SellMilk(const pair<long long, pair<int, int> >& MilkRes, vector<int>& Cows, vector<pair<int, int> >& Milk, long long& Profit) {
    Profit += MilkRes.first;
    for (int i = 0; i < MilkRes.second.first; i++) Milk.pop_back();
    if (Milk.size() > 0) Milk[Milk.size() - 1].first -= MilkRes.second.second;
    Cows.pop_back();
    return;
}

int main() {
    int N, M, R;
    long long Profit = 0;
    pair<long long, pair<int, int> > MilkRes;
    fin >> N >> M >> R;
    vector<int> Cows(N), Rentals(R);
    vector<pair<int, int> > Milk;
    for (int i = 0; i < N; i++) fin >> Cows[i];
    for (int i = 0; i < M; i++) {
        pair<int, int> NewMilk;
        fin >> NewMilk.first >> NewMilk.second;
        Milk.push_back(NewMilk);
    }
    for (int i = 0; i < R; i++) fin >> Rentals[i];
    sort(all(Cows));
    sort(all(Milk), PerGalSort);
    sort(all(Rentals));
    while (Cows.size() > 0 and (Rentals.size() > 0 or Milk.size() > 0)) {
        if (Milk.size() > 0) MilkRes = MilkCow(Cows.back(), Milk);
        if (Cows.size() > Rentals.size() and Milk.size() > 0) SellMilk(MilkRes, Cows, Milk, Profit);
        else {
            if (Milk.size() > 0 and MilkRes.first >= Rentals.back()) SellMilk(MilkRes, Cows, Milk, Profit);
            else {
                Profit += Rentals.back();
                Rentals.pop_back();
                Cows.erase(Cows.begin());
            }
        }
    }
    fout << Profit << "\n";
    return 0;
}
