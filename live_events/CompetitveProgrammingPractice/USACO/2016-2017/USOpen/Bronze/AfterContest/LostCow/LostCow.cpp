/*
Test outputs

9
*/

#include <fstream>

using namespace std;

ofstream fout("lostcow.out");
ifstream fin("lostcow.in");

int main() {

    //Vars
    int x, y, NewDist, CurLoc;
    bool IsPos;
    int DistTrav = 0;

    fin >> x >> y;
    y -= x;
    x = 0;
    if (y == 0) {
        fout << y << "\n";
        return 0;
    }
    IsPos = y > 0;
    CurLoc = 0;
    NewDist = 1;
    while (true) {
        if (NewDist >= y and IsPos) {
            DistTrav += y - CurLoc;
            fout << DistTrav << "\n";
            return 0;
        }
        else if (NewDist <= y and not IsPos) {
            DistTrav += CurLoc - y;
            fout << DistTrav << "\n";
            return 0;
        }
        else {
            if (NewDist > 0)
                DistTrav += NewDist - CurLoc;
            else
                DistTrav += CurLoc - NewDist;
            CurLoc = NewDist;
            NewDist *= -2;
        }
    }
}
