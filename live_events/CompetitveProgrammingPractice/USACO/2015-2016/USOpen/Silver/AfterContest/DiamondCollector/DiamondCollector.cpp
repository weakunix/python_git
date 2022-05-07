#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("diamond.out");
ifstream fin("diamond.in");

int main() {
    int N, K, Left = 0, Right = 0, Best = 0;
    fin >> N >> K;
    vector<int> Diamond(N), LessThan(N, 1), GreaterThan(N, 1);
    for (int i = 0; i < N; i++) fin >> Diamond[i];
    sort(all(Diamond));
    while (Left < N - 1) {
        if (Diamond[Right] - Diamond[Left] <= K and Right < N - 1) Right++;
        else Left++;
        if (Diamond[Right] - Diamond[Left] <= K) {
            LessThan[Right] = max(Right - Left + 1, LessThan[Right]);
            if (Left > 0) GreaterThan[Left - 1] = max(Right - Left + 1, GreaterThan[Left - 1]);
        }
    }
    for (int i = 1; i < N; i++) LessThan[i] = max(LessThan[i - 1], LessThan[i]);
    for (int i = N - 1; i >= 0; i--) {
        if (i == N - 1) GreaterThan[i] = 0;
        else GreaterThan[i] = max(GreaterThan[i + 1], GreaterThan[i]);
    }
    for (int i = 0; i < N; i++) Best = max(LessThan[i] + GreaterThan[i], Best);
    fout << Best << "\n";
    return 0;
}
