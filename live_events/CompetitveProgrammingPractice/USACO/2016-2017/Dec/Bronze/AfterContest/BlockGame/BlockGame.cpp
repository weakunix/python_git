/*
Test outputs

1:
2
2
2
1
0
1
1
0
0
0
0
0
0
0
2
0
0
1
1
1
1
0
0
1
0
0
*/

#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

ofstream fout("blocks.out");
ifstream fin("blocks.in");

map<char, int> GenLetterMap() {
    map<char, int> LetterMap;
    for (char c = 'a'; c <= 'z'; c++) {
        LetterMap[c] = 0;
    }
    return LetterMap;
}

map<char, int> GetLetterCount(string Word) {
    map<char, int> LetterCount = GenLetterMap();
    for (char c : Word) {
        LetterCount[c] += 1;
    }
    return LetterCount;
}

int main() {

    //Vars
    int N;
    vector<vector<string> > Words;
    map<char, int> Word1, Word2, AllCards = GenLetterMap();

    //Temp vars
    string temp_str;
    vector<string> temp_vect_str;

    fin >> N;
    for (int i = 0; i < N; i++) {
        temp_vect_str.clear();
        for (int k = 0; k < 2; k++) {
            fin >> temp_str;
            temp_vect_str.push_back(temp_str);
        }
        Words.push_back(temp_vect_str);
    }
    for (vector<string> i : Words) {
        Word1 = GetLetterCount(i[0]);
        Word2 = GetLetterCount(i[1]);
        for (char c = 'a'; c <= 'z'; c++) {
            AllCards[c] += max(Word1[c], Word2[c]);
        }
    }
    for (char c = 'a'; c <= 'z'; c++) {
        fout << AllCards[c] << "\n";
    }
    return 0;
}
