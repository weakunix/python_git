#include <fstream>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <algorithm>

using namespace std;

ofstream fout("evolution.out");
ifstream fin("evolution.in");

#define all(v) v.begin(), v.end()

int main() {
    int N, K;
    vector<int> Nodes1, Nodes2, Intersection;
    vector<string> Traits;
    unordered_map<string, vector<int> > TraitMap;
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> K;
        vector<string> CurNode(K);
        for (int k = 0; k < K; k++) fin >> CurNode[k];
        for (string s : CurNode) {
            if (TraitMap.count(s) == 0) {
                TraitMap[s] = {i};
                Traits.push_back(s);
            }
            else TraitMap[s].push_back(i);
        }
    }
    for (int i = 0; i < Traits.size() - 1; i++) {
        for (int k = i + 1; k < Traits.size(); k++) {
            Nodes1 = TraitMap[Traits[i]];
            Nodes2 = TraitMap[Traits[k]];
            Intersection.clear();
            set_intersection(all(Nodes1), all(Nodes2), back_inserter(Intersection));
            if (Intersection.size() != 0 and Intersection.size() != min(Nodes1.size(), Nodes2.size())) {
                fout << "no\n";
                return 0;
            }
        }
    }
    fout << "yes\n";
    return 0;
}
