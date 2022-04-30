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

long long MilkCow(int MilkRemain, vector<pair<int, int> >& Milk) {
    long long Profit = 0;
    while (MilkRemain > 0 and Milk.size() > 0) {
        long long a = Milk.back().first, b = Milk.back().second;
        if (MilkRemain >= Milk.back().first) {
            Profit += a * b;
            MilkRemain -= a;
            Milk.pop_back();
        }
        else {
            Profit += MilkRemain * b;
            Milk[Milk.size() - 1].first -= MilkRemain;
            MilkRemain = 0;
        }
    }
    return Profit;
}

long long SimMilkCow(int MilkRemain, vector<pair<int, int> > Milk) {
    return MilkCow(MilkRemain, Milk);
}

int main() {
    int N, M, R;
    long long Profit = 0;
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
        if (Cows.size() > Rentals.size() and Milk.size() > 0) {
            Profit += MilkCow(Cows.back(), Milk);
            Cows.pop_back();
        }
        else {
            if (SimMilkCow(Cows.back(), Milk) >= Rentals.back()) {
                Profit += MilkCow(Cows.back(), Milk);
                Cows.pop_back();
            }
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
