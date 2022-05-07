#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("herding.out");
ifstream fin("herding.in");

int GetBestMin(const vector<int>& CowLoc, int N) {
    int Left = 0, Right = 0, Best = 100000;
    while (Left < N - 1) {
        if (CowLoc[Right] - CowLoc[Left] < N and Right < N - 1) Right++;
        else Left++;
        assert(Left <= Right);
        if (CowLoc[Right] - CowLoc[Left] < N) {
            if (Right - Left == N - 2 and CowLoc[Right] - CowLoc[Left] == N - 2) Best = min(2, Best);
            else Best = min(N - (Right - Left + 1), Best);
        }
    }
    return Best;
}

int GetBestMax(const vector<int>& CowLoc, int N) {
    return max(CowLoc.back() - CowLoc[1] - (N - 2), CowLoc[N - 2] - CowLoc[0] - (N - 2));
}

int main() {
    int N;
    fin >> N;
    vector<int> CowLoc(N);
    for (int i = 0; i < N; i++) fin >> CowLoc[i];
    sort(all(CowLoc));
    fout << GetBestMin(CowLoc, N) << "\n" << GetBestMax(CowLoc, N) << "\n";
    return 0;
}
