

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string s, t, inpt, NewS, NewT;
    int Q;
    vector<vector<char> > Queries;

    cin >> s >> t >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> inpt;
        vector<char> Newq;
        for (int k = 0; k < inpt.size(); k++) {
            Newq.push_back(inpt[k]);
        }
        Queries.push_back(Newq);
    }
    for (vector<char> q : Queries) {
        NewS = "";
        NewT = "";
        for (char i : s) {
            if (find(q.begin(), q.end(), i) != q.end())
                NewS += i;
        }
        for (char i : t) {
            if (find(q.begin(), q.end(), i) != q.end())
                NewT += i;
        }
        if (NewS == NewT)
            cout << "Y";
        else
            cout << "N";
    }
    cout << "\n";
}
