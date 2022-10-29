#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

int N;
vector<int> InputOrd;
vector<int> SortedOrd;
unordered_map<int, int> InputMap;

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int Cur;
        cin >> Cur;
        InputOrd.push_back(Cur);
        SortedOrd.push_back(Cur);
    }

    sort(all(SortedOrd));

    for (int i = 0; i < N; i++) InputMap[SortedOrd[i]] = i;

    int Gcd = 1, CurIdx = 0;
    vector<int> OneTwo = {0}, OneThree = {0};
    
    while (CurIdx < N) {
        while (2 * Gcd > SortedOrd[CurIdx]) {
            CurIdx++;
            OneTwo.push_back(OneTwo.back());
            if (CurIdx >= N) break;
        }
        
        if (CurIdx >= N) break;
        
        OneTwo[CurIdx]++;
        Gcd++;
    }

    Gcd = 1;
    CurIdx = 0;

    while (CurIdx < N) {
        while (3 * Gcd > SortedOrd[CurIdx]) {
            CurIdx++;
            OneThree.push_back(OneThree.back());
            if (CurIdx >= N) break;
        }
        
        if (CurIdx >= N) break;
        
        OneThree[CurIdx]++;
        Gcd++;
    }

    for (int i : InputOrd) cout << 2 * (OneTwo[InputMap[i]] + OneThree[InputMap[i]]) + i << "\n";

    return 0;
}
