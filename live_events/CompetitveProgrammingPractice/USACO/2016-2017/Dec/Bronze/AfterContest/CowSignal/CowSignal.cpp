/*
Test outputs

1:
XXXXXX..
XXXXXX..
XX....XX
XX....XX
XXXXXX..
XXXXXX..
XX....XX
XX....XX
XXXXXX..
XXXXXX..
*/

#include <fstream>
#include <vector>

#include <iostream>

using namespace std;

ofstream fout("cowsignal.out");
ifstream fin("cowsignal.in");

int main() {

    //Vars
    int M, N, K, CharCount;
    char CurChar;
    vector<string> Lines;
    string NewLine;

    //Temp vars
    string inpt_str;
    
    fin >> M >> N >> K;
    for (int i = 0; i < M; i++) {
        fin >> inpt_str;
        Lines.push_back(inpt_str);
    }
    for (string i : Lines) {
        CurChar = 'X';
        CharCount = 0;
        NewLine = "";
        for (int k = 0; k < N; k++) {
            if (i[k] == CurChar)
                CharCount += 1;
            else {
                for (int j = 0; j < CharCount * K; j++) {
                    NewLine += CurChar;
                }
                CurChar = i[k];
                CharCount = 1;
            }
        }

        for (int j = 0; j < CharCount * K; j++) {
            NewLine += CurChar;
        }

        for (int k = 0; k < K; k++) {
            fout << NewLine << "\n";
        }
    }
    return 0;
}
