#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

int main() {
    int N, M, Lead = 0, Ans = 0;
    vector<int> JohnMittens = {0}, JaneMittens = {0};
    cin >> N >> M;
    vector<pii> John(N), Jane(M);
    for (int i = 0; i < N; i++) cin >> John[i].first >> John[i].second;
    for (int i = 0; i < M; i++) cin >> Jane[i].first >> Jane[i].second;
    for (const pii& p : John) {
        int CurSpeed = p.first, CurTime = p.second;
        while (CurTime > 0) {
            JohnMittens.push_back(JohnMittens.back() + CurSpeed);
            CurTime--;
        }
    }
    for (const pii& p : Jane) {
        int CurSpeed = p.first, CurTime = p.second;
        while (CurTime > 0) {
            JaneMittens.push_back(JaneMittens.back() + CurSpeed);
            CurTime--;
        }
    }
    for (int i = 0; i < JohnMittens.size(); i++) {
        if (JohnMittens[i] > JaneMittens[i] and Lead != 1) {
            Lead = 1;
            Ans++;
        }
        if (JaneMittens[i] > JohnMittens[i] and Lead != -1) {
            Lead = -1;
            Ans++;
        }
    }
    cout << Ans - (Lead != 0) << "\n";
    return 0;
}
