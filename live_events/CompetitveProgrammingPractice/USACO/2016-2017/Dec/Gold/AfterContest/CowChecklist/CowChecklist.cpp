#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

int GetDist(const simps& a, const simps& b) {
    int x = a.first - b.first, y = a.second - b.second;
    return x * x + y * y;
}

int main() {
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);

    int H, G;
    cin >> H >> G;
    vector<simps> HCows(H), GCows(G);
    vector<vector<int> > DpEndOnH(G + 1), DpEndOnG(G + 1);
    for (int i = 0; i <= G; i++) {
        DpEndOnH[i].resize(H);
        DpEndOnG[i].resize(H);
    }
    for (int i = 0; i < H; i++) cin >> HCows[i].first >> HCows[i].second;
    for (int i = 0; i < G; i++) cin >> GCows[i].first >> GCows[i].second;

    for (int g = 0; g <= G; g++) {
        for (int h = 0; h < H; h++) {
            if (g == 0 and h == 0) DpEndOnG[0][0] = 2e9;
            else if (g == 0) {
                DpEndOnH[0][h] = DpEndOnH[0][h - 1] + GetDist(HCows[h], HCows[h - 1]);
                DpEndOnG[0][h] = 2e9;
            }
            else if (h == 0) {
                if (g == 1) DpEndOnG[1][0] = GetDist(HCows[0], GCows[0]);
                else DpEndOnG[g][0] = DpEndOnG[g - 1][0] + GetDist(GCows[g - 1], GCows[g - 2]);
                DpEndOnH[g][0] = 2e9;
            }
            else {
                DpEndOnH[g][h] = min(DpEndOnH[g][h - 1] + GetDist(HCows[h], HCows[h - 1]), DpEndOnG[g][h - 1] + GetDist(HCows[h], GCows[g - 1]));
                DpEndOnG[g][h] = DpEndOnH[g - 1][h] + GetDist(GCows[g - 1], HCows[h]);
                if (g > 1) DpEndOnG[g][h] = min(DpEndOnG[g - 1][h] + GetDist(GCows[g - 1], GCows[g - 2]), DpEndOnG[g][h]);
            }
        }
    }
    cout << DpEndOnH[G][H - 1] << "\n";
    return 0;
}
