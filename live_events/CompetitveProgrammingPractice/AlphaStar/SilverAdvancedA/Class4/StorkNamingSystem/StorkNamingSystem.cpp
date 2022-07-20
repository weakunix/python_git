#include <iostream>
#include <string>

using namespace std;

int main() {
    bool Found = false;
    string Id, Name;
    cin >> Id;
    while (cin >> Name) {
        string CurId = "";
        for (char c : Name) {
            if ((c == 'A' or c == 'B') or c == 'C') CurId += '2';
            else if ((c == 'D' or c == 'E') or c == 'F') CurId += '3';
            else if ((c == 'G' or c == 'H') or c == 'I') CurId += '4';
            else if ((c == 'J' or c == 'K') or c == 'L') CurId += '5';
            else if ((c == 'M' or c == 'N') or c == 'O') CurId += '6';
            else if ((c == 'P' or c == 'R') or c == 'S') CurId += '7';
            else if ((c == 'T' or c == 'U') or c == 'V') CurId += '8';
            else if ((c == 'W' or c == 'X') or c == 'Y') CurId += '9';
        }
        if (CurId == Id) {
            Found = true;
            cout << Name << "\n";
        }
    }
    if (not Found) cout << "NONE\n";
    return 0;
}
