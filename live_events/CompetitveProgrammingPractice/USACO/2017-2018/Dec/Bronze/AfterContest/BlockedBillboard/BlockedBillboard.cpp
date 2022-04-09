/*
Test outputs

1:
17
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ofstream fout("billboard.out");
ifstream fin("billboard.in");

int AreaIntersect(int a, int b, int c, int d, int e, int f, int g, int h) {
    return max(min(max(a, c), max(e, g)) - max(min(a, c), min(e, g)), 0) * max(min(max(f, h), max(b, d)) - max(min(f, h), min(b, d)), 0);
}

int main() {

    //Vars
    int a1;
    int b1;
    int c1;
    int d1;
    int a2;
    int b2;
    int c2;
    int d2;
    int e;
    int f;
    int g;
    int h;

    fin >> a1 >> b1 >> c1 >> d1 >> a2 >> b2 >> c2 >> d2 >> e >> f >> g >> h;
    fout << (c1 - a1) * (d1 - b1) + (c2 - a2) * (d2 - b2) - AreaIntersect(a1, b1, c1, d1, e, f, g, h) - AreaIntersect(a2, b2, c2, d2, e, f, g, h) << "\n";
    return 0;
}
