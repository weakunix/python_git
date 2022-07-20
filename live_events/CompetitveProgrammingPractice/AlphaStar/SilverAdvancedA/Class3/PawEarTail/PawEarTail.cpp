#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, Best = 0;
    vector<int> Paws = {0}, Ears = {0}, Tails = {0};
    cin >> N;
    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
        Paws.push_back(Paws.back());
        Ears.push_back(Ears.back());
        Tails.push_back(Tails.back());
        if (c == 'P') Paws.back()++;
        else if (c == 'E') Ears.back()++;
        else Tails.back()++;
    }
    for (int i = 0; i < N; i++) Best = max(max({Paws[i], Ears[i], Tails[i]}) + max({Paws.back() - Paws[i], Ears.back() - Ears[i], Tails.back() - Tails[i]}), Best);
    cout << Best << "\n";
    return 0;
}
