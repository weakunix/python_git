#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

ofstream fout("maxcross.out");
ifstream fin("maxcross.in");

int main() {
    int N, K, B, MinFix;
    fin >> N >> K >> B;
    MinFix = B;
    unordered_set<int> Broken;
    vector<int> PreB = {0};
    for (int i = 0; i < B; i++) {
        int b;
        fin >> b;
        Broken.insert(b);
    }
    for (int i = 1; i <= N; i++) {
        PreB.push_back(PreB.back());
        if (Broken.count(i) > 0) PreB[i]++;
    }
    for (int i = K; i <= N; i++) MinFix = min(PreB[i] - PreB[i - K], MinFix);
    fout << MinFix << "\n";
    return 0;
}
