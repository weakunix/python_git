#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("angry.out");
ifstream fin("angry.in");

void NegateSortVect(vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); it++) *it *= -1;
    sort(all(v));
    return;
}

vector<int> GetMinExplosionPowers(vector<int>& Haybales, int N) {
    NegateSortVect(Haybales);
    int CurPow = 0, CurHaybale = Haybales[0];
    vector<int> MinExplosionPowers = {0, 0};
    for (int i = 1; i < N; i++) {
        if (Haybales[i] - CurHaybale <= CurPow) MinExplosionPowers.push_back(CurPow);
        else {
            if (Haybales[i] - Haybales[i - 1] <= CurPow + 1) {
                CurHaybale = Haybales[i - 1];
                CurPow++;
            }
            else {
                CurPow = Haybales[i] - Haybales[i - 1];
                CurHaybale = Haybales[i - 1];
            }
            MinExplosionPowers.push_back(CurPow);
        }
    }
    MinExplosionPowers.push_back(0);
    assert(MinExplosionPowers.size() == N + 2);
    return MinExplosionPowers;
}

string PrintRes(int Ans) {
    if (Ans % 2 == 0) return to_string(Ans / 2) + ".0";
    else return to_string(Ans / 2) + ".5";
}

int main() {
    int N, Best = 1e9;
    fin >> N;
    vector<int> Haybales(N), ExplodeToLeft, ExplodeToRight;
    for (int i = 0; i < N; i++) fin >> Haybales[i];
    ExplodeToRight = GetMinExplosionPowers(Haybales, N);
    reverse(all(ExplodeToRight));
    ExplodeToLeft = GetMinExplosionPowers(Haybales, N);
    for (int i = 0; i <= N; i++) Best = min(max(2 * max(ExplodeToLeft[i], ExplodeToRight[i + 1]) + 2, Haybales[i] - Haybales[i - 1]), Best);
    for (int i = 1; i <= N; i++) Best = min(2 * max(ExplodeToLeft[i], ExplodeToRight[i]), Best);
    fout << PrintRes(Best) << "\n";
    return 0;
}
