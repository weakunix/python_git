#include <iostream>
#include <string>

using namespace std;

int main() {
    int TSize;
    string S, T, Ans;
    cin >> S >> T;
    TSize = T.size();
    for (char c : S) {
        Ans += c;
        if (Ans.size() >= TSize) {
            if (Ans.substr(Ans.size() - TSize, TSize) == T) Ans = Ans.substr(0, Ans.size() - TSize);
        }
    }
    cout << Ans << "\n";
    return 0;
}
