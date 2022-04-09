/*
Test outputs

1:
6
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

ofstream fout("paint.out");
ifstream fin("paint.in");

int main() {
    
    //Vars
    int a;
    int b;
    int c;
    int d;
    int Intersection;

    fin >> a >> b >> c >> d;
    if (d >= b)
        Intersection = max(c - b, 0);
    else
        Intersection = max(a - d, 0);
    fout << max(b, d) - min(a, c) - Intersection << "\n";
    return 0;
}
