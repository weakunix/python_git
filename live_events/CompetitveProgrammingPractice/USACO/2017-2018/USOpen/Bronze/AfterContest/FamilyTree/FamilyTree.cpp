#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

ofstream fout("family.out");
ifstream fin("family.in");

vector<string> GetCowHist(string Cow, const unordered_map<string, string>& ChildParent) {
    vector<string> Hist = {Cow};
    while (ChildParent.count(Cow) > 0) {
        Cow = ChildParent.at(Cow);
        Hist.push_back(Cow);
    }
    return Hist;
}

string GetDirRelationship(int Size) {
    Size--;
    if (Size == 0) return "mother";
    string Relationship = "";
    for (int i = 0; i < Size - 1; i++) Relationship += "great-";
    return Relationship + "grand-mother";
}

string GetOtherRelationship(int Size) {
    Size--;
    string Relationship = "";
    for (int i = 0; i < Size; i++) Relationship += "great-";
    return Relationship + "aunt";
}

int main() {
    int N, Hist1Size = 0, Hist2Size = 0;
    unordered_map<string, string> ChildParent;
    string C1, C2;
    vector<string> Hist1, Hist2;
    fin >> N >> C1 >> C2;
    for (int i = 0; i < N; i++) {
        string a, b;
        fin >> a >> b;
        ChildParent[b] = a;
    }
    Hist1 = GetCowHist(C1, ChildParent);
    Hist2 = GetCowHist(C2, ChildParent);
    if (Hist1.back() != Hist2.back()) {
        fout << "NOT RELATED\n";
        return 0;
    }
    while (Hist1.size() > 0 and Hist2.size() > 0) {
        if (Hist1.back() == Hist2.back()) {
            Hist1.pop_back();
            Hist2.pop_back();
        }
        else break;
    }
    Hist1Size = Hist1.size();
    Hist2Size = Hist2.size();
    if (min(Hist1Size, Hist2Size) == 0) {
        if (Hist1Size == 0) fout << C1 << " is the " << GetDirRelationship(Hist2Size) << " of " << C2 << "\n";
        else fout << C2 << " is the " << GetDirRelationship(Hist1Size) << " of " << C1 << "\n";
    }
    else if (Hist1Size == 1 and Hist2Size == 1) fout << "SIBLINGS\n";
    else if (min(Hist1Size, Hist2Size) == 1) {
        if (Hist1Size == 1) fout << C1 << " is the " << GetOtherRelationship(Hist2Size - 1) << " of " << C2 << "\n";
        else fout << C2 << " is the " << GetOtherRelationship(Hist1Size - 1) << " of " << C1 << "\n";
    }
    else fout << "COUSINS\n";
    return 0;
}
