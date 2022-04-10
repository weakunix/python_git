#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//#include <iostream>

using namespace std;

ofstream fout("bcs.out");
ifstream fin("bcs.in");

vector<string> SimpPiece(vector<string> CurPiece) {
    bool Done;
    string Left, Right;
    while (CurPiece.size() > 0) {
        Done = true;
        if (count(CurPiece[0].begin(), CurPiece[0].end(), '#') ==  0) {
            CurPiece.erase(CurPiece.begin());
            Done = false;
        }
        if (CurPiece.size() > 0 and count(CurPiece[CurPiece.size() - 1].begin(), CurPiece[CurPiece.size() - 1].end(), '#') ==  0) {
            CurPiece.pop_back();
            Done = false;
        }
        if (Done) break;
    }
    while (CurPiece[0].size() > 0) {
        Done = true;
        Left = "";
        Right = "";
        for (int i = 0; i < CurPiece.size(); i++) {
            Left += CurPiece[i][0];
            Right += CurPiece[i][CurPiece[i].size() - 1];
        }
        if (count(Left.begin(), Left.end(), '#') == 0) {
            for (int i = 0; i < CurPiece.size(); i++) {
                CurPiece[i].erase(0, 1);
            }
            Done = false;
        }
        if (CurPiece[0].size() > 0 and count(Right.begin(), Right.end(), '#') == 0) {
            for (int i = 0; i < CurPiece.size(); i++) {
                CurPiece[i].erase(CurPiece[i].size() - 1, 1);
            }
            Done = false;
        }
        if (Done) break;
    }
    return CurPiece;
}

int main() {
    int N, K;
    fin >> N >> K;
    bool Works;
    string temp_str;
    vector<string> Target, CurPiece, OtherPiece;
    vector<vector<string> > Pieces;
    for (int k = 0; k <= K; k++) {
        CurPiece.clear();
        for (int i = 0; i < N; i++) {
            fin >> temp_str;
            CurPiece.push_back(temp_str);
        }
        if (k == 0) Target = SimpPiece(CurPiece);
        else Pieces.push_back(SimpPiece(CurPiece));
    }
    for (int k = 0; k < Pieces.size(); k++) {
        vector<string> v = Pieces[k];
        if (k == 3)
            fout << "";
        if (v.size() <= Target.size() and v[0].size() <= Target[0].size()) {
            for (int i = 0; i <= (Target.size() - v.size()); i++) {
                for (int j = 0; j <= (Target[0].size() - v[0].size()); j++) {
                    OtherPiece = Target;
                    Works = true;
                    for (int a = 0; a < v.size(); a++) {
                        for (int b = 0; b < v[0].size(); b++) {
                            if (v[a][b] == '#' and Target[a + i][b + j] == '.') {
                                Works = false;
                                break;
                            }
                            if (v[a][b] == '#') OtherPiece[a + i][b + j] = '.';
                        }
                        if (not Works) break;
                    }
                    if (Works)
                        OtherPiece = SimpPiece(OtherPiece);
                        auto index = find(Pieces.begin(), Pieces.end(), OtherPiece);
                        if (index != Pieces.end()) {
                            fout << k + 1 << " " << index - Pieces.begin() + 1 << "\n";
                            return 0;
                        }
                }
            }
        }
    }
    return 1;
}
