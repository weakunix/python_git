/*
Test outputs

1:
22
*/

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include <iostream>

using namespace std;

ofstream fout("cownomics.out");
ifstream fin("cownomics.in");

int main() {

    int N, M, UniqGenomes = 0;
    fin >> N >> M;
    vector<string> Spots(N), Plains(N);
    unordered_map<char, int> GenomeDict = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
    for (int i = 0; i < N; i++) fin >> Spots[i];
    for (int i = 0; i < N; i++) fin >> Plains[i];
    for (int i = 0; i < M - 2; i++) {
        for (int k = i + 1; k < M - 1; k++) {
            for (int j = k + 1; j < M; j++) {
                vector<bool> HasSpotGenome(64);
                for (string s : Spots) HasSpotGenome[16 * GenomeDict[s[i]] + 4 * GenomeDict[s[k]] + GenomeDict[s[j]]] = true;
                bool IsUniq = true;
                for (string s : Plains) {
                    if (HasSpotGenome[16 * GenomeDict[s[i]] + 4 * GenomeDict[s[k]]     + GenomeDict[s[j]]]) {
                        IsUniq = false;
                        break;
                    }
                }
                if (IsUniq) UniqGenomes++;
            }
        }
    }
    fout << UniqGenomes << "\n";
    return 0;
}
