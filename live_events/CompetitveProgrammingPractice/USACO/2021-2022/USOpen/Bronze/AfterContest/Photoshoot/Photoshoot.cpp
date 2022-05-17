#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int N;
    string Line, Sub;
    vector<string> New;
    cin >> N >> Line;
    for (int i = 0; i < N; i++) {
        Sub += Line.substr(i, 1);
        if (i % 2 == 1) {
            if (Sub != "HH" and Sub != "GG") {
                if (Sub == "HG") Sub = "1";
                else Sub = "0";
                if (New.size() == 0 or New.back() != Sub) New.push_back(Sub);
            }
            Sub = "";
        }
    }
    while (New.size() > 0 and New.back() == "1") New.pop_back();
    cout << New.size() << "\n";
    return 0;
}
