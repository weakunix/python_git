#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

set<char> pcl = {'P', 'C', 'L', 'A', 'S', 'I'};

int main() {
    string s;
    cin >> s;
    cout << (pcl.count(s[0]) ? "YES\n" : "NO\n");
	return 0;
}
