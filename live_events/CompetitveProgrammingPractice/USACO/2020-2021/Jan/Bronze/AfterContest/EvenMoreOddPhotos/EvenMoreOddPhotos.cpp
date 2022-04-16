#include <iostream>

using namespace std;

int main() {
    int N, Even = 0, Odd = 0, Num, Count = 0;
    bool IsEven = false;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> Num;
        if (Num % 2 == 0) Even++;
        else Odd++;
    }
    while (Even + Odd > 0) {
        IsEven = not IsEven;
        if (IsEven) {
            if (Even > 0) Even--;
            else if (Odd > 1) Odd -= 2;
            else break;
        }
        else {
            if (Odd > 0) Odd--;
            else break;
        }
        Count++;
    }
    if (Odd == 1) Count--;
    cout << Count << "\n";
    return 0;
}
