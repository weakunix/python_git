#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

ll GetInterestingCount(const char a, const char b, const ll X, const ll Y) {
    ll Count = 0;
    for (int i = 3; i <= 17; i++) {
        string Cur = "";
        for (int j = 0; j < i; j++) Cur += a;
        for (int j = 0; j < i; j++) {
            if ((a != '0' and b != '0') or ((a == '0' and j == 0) or (b == '0' and j != 0))) {
                string New = Cur;
                ll CurNum;
                New[j] = b;
                CurNum = stoll(New);
                if (CurNum == 222)
                    cout << "";
                if (CurNum >= X and CurNum <= Y) Count++;
            }
        }
    }
    return Count;
}

int main() {
    ll X, Y, Ans = 0;
    cin >> X >> Y;
    for (char a = '0'; a <= '9'; a++) {
        for (char b = '0'; b <= '9'; b++) {
            if (a != b) Ans += GetInterestingCount(a, b, X, Y);
        }
    }
    cout << Ans << "\n";
    return 0;
}
