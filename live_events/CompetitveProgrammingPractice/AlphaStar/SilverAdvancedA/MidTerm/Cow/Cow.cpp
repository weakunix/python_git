#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
    int N;
    string Text;
    ll Ans = 0;
    cin >> N >> Text;
    vector<int> C(N), Co(N);
    for (int i = 0; i < N; i++) {
        if (Text[i] == 'C') C[i]++;
        if (i > 0) C[i] += C[i - 1];
    }
    for (int i = 0; i < N; i++) {
        if (Text[i] == 'O') Co[i] = C[i];
        if (i > 0) Co[i] += Co[i - 1];
    }
    for (int i = 0; i < N; i++) {
        if (Text[i] == 'W') Ans += Co[i];
    }
    cout << Ans << "\n";
    return 0;
}
