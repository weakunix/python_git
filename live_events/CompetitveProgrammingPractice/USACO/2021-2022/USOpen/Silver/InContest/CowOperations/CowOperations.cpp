
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    string s, temp_str;
    string temp_char;
    int Q, l, r, CountC, CountO, CountW;
    vector<vector<int> > SubStrings;

    cin >> s >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> l >> r;
        SubStrings.push_back({l, r});
    }
    for (vector<int> i : SubStrings) {
        l = i[0] - 1;
        r = i[1];
        temp_str = s.substr(l, r - l);
        CountC = 0;
        CountO = 0;
        CountW = 0;
        for (int k = 0; k < temp_str.size(); k++) {
            temp_char = temp_str.substr(k, 1); 
            if (temp_char == "C")
                CountC += 1;
            else if (temp_char == "O")
                CountO += 1;
            else
                CountW += 1;
        }
        if ((CountO + CountW) % 2 == 1)
            cout << "N";
        else if ((CountC + min(CountO, CountW) % 2) % 2 == 1)
            cout << "Y";
        else
            cout << "N";

    }
    cout << "\n";
}
