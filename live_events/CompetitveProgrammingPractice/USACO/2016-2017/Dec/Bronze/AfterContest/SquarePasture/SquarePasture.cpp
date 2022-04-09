/*
Test outputs

1:
49
*/

#include <fstream>
#include <cmath>

using namespace std;

ofstream fout("square.out");
ifstream fin("square.in");

int main() {
    
    //Vars
    int blx1, bly1, trx1, try1, blx2, bly2, trx2, try2;
    
    fin >> blx1 >> bly1 >> trx1 >> try1 >> blx2 >> bly2 >> trx2 >> try2;
    fout << pow(max(max(trx1, trx2) - min(blx1, blx2), max(try1, try2) - min(bly1, bly2)), 2);
    return 0;
}
