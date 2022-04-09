/*
Test outputs

1:
76
*/

#include <fstream>
#include <algorithm>

using namespace std;

ofstream fout("pails.out");
ifstream fin("pails.in");

int main() {

    //Vars
    int X, Y, M, MaxMilk = 0;

    fin >> X >> Y >> M;
    for (int i = 0; i <= M / X; i++) {
        MaxMilk = max((M - i * X) / Y * Y + i * X, MaxMilk);
    }
    fout << MaxMilk << "\n";
    return 0;
}
