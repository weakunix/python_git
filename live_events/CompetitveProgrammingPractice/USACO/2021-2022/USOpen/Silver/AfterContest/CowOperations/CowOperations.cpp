#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int Q;
    string s;
    cin >> s >> Q;
    vector<int> C = {0}, O = {0}, W = {0};
    for (char c : s) {
        C.push_back(C.back());
        O.push_back(O.back());
        W.push_back(W.back());
        if (c == 'C') C.back()++;
        else if (c == 'O') O.back()++;
        else W.back()++;
    }
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        if ((O[r] - O[l - 1] + W[r] - W[l - 1]) % 2 == 0 and (C[r] - C[l - 1] + O[r] - O[l - 1]) % 2 == 1) cout << "Y";
        else cout << "N";
    }
    cout << "\n";
    return 0;
}
