#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string NewStr(const string Original) {
    string New = "0";
    for (char c : Original) {
        if (c == '1') continue;
        if (c == '0') New = "0";
        if (c == '+') New += "1";
        else New += "2";
    }
    return New;
}

void Subcase() {
    const int ModVal = 1e9 + 7;
    int N, B, E;
    string Bessie, Elsie;
    vector<vector<int> > DpBessie, DpElsie;
    cin >> N >> Bessie >> Elsie;
    Bessie = NewStr(Bessie);
    Elsie = NewStr(Elsie);
    B = Bessie.size();
    E = Elsie.size();
    DpBessie.resize(E);
    DpElsie.resize(E);
    for (int i = 0; i < E; i++) {
        DpBessie[i].resize(B);
        DpElsie[i].resize(B);
    }
    for (int i = 0; i < B; i++) DpBessie[0][i] = 1;
    for (int i = 0; i < E; i++) DpElsie[i][0] = 1;
    for (int b = 1; b < B; b++) {
        for (int e = 1; e < E; e++) {
            if (Elsie[e] == Bessie[b]) DpBessie[e][b] = DpBessie[e][b - 1];
            else DpBessie[e][b] = (DpBessie[e][b - 1] + DpElsie[e][b - 1]) % ModVal;
            DpElsie[e][b] = (DpBessie[e - 1][b] + DpElsie[e - 1][b]) % ModVal;
        }
    }
    cout << (DpBessie[E - 1][B - 1] + DpElsie[E - 1][B - 1]) % ModVal << "\n";
    return;
}

int main() {
    //freopen("test.txt", "r", stdin);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) Subcase();
    return 0;
}
