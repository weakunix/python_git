/*
Test outputs

1:
15
*/

#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

ofstream fout("billboard.out");
ifstream fin("billboard.in");

int main() {

    //Vars
    int blx1, bly1, trx1, try1, blx2, bly2, trx2, try2;
    bool XCovered = false, YCovered = false;
    
    fin >> blx1 >> bly1 >> trx1 >> try1 >> blx2 >> bly2 >> trx2 >> try2;
    if (blx2 <= blx1 and trx2 >= trx1 and (bly2 <= bly1 or try2 >= try1))
        XCovered = true;
    if (bly2 <= bly1 and try2 >= try1 and (blx2 <= blx1 or bly2 >= bly1))
        YCovered = true;
    if (XCovered and YCovered)
        fout << 0 << "\n";
    else if (XCovered)
        fout << (trx1 - blx1) * ((try1 - bly1) - max(min(try1, try2) - max(bly1, bly2), 0)) << "\n";
    else if (YCovered)
        fout << ((trx1 - blx1) - max(min(trx1, trx2) - max(blx1, blx2), 0)) * (try1 - bly1) << "\n";
    else
        fout << (trx1 - blx1) * (try1 - bly1) << "\n";
    return 0;
}
