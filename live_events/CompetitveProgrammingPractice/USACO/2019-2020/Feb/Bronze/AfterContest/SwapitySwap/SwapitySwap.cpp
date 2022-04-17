#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

ofstream fout("swap.out");
ifstream fin("swap.in");

vector<int> SimOperation(const vector<int>& Original, const vector<int>& Operation) {
    vector<int> New;
    for (int i : Operation) New.push_back(Original[i]);
    return New;
}

int main() {
    int N, K, A1, A2, B1, B2, Count = 1;
    vector<vector<int> > Operations;
    fin >> N >> K >> A1 >> A2 >> B1 >> B2;
    vector<int> CurOrd(N);
    for (int i = 0; i < N; i++) CurOrd[i] = i;
    A1--;
    B1--;
    reverse(CurOrd.begin() + A1, CurOrd.begin() + A2);
    reverse(CurOrd.begin() + B1, CurOrd.begin() + B2);
    Operations.push_back(CurOrd);
    while (pow(2, Count) <= K) {
        Operations.push_back(SimOperation(Operations.back(), Operations.back()));
        Count++;
    }
    for (int i = 0; i < N; i++) CurOrd[i] = i + 1;
    Count = Operations.size() - 1;
    while (Count >= 0) {
        if (pow(2, Count) <= K) {
            CurOrd = SimOperation(CurOrd, Operations[Count]);
            K -= pow(2, Count);
        }
        Count--;
    }
    for (int i : CurOrd) fout << i << "\n";
    return 0;
}
