#include <iostream>
#include <vector>
#include <utility>
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

int n;
ll sm = 0;
vector<int> books;

int main() {
    cin >> n;
    books.resize(n);
    for (int i = 0; i < n; i++) cin >> books[i];
    sort(all(books));
    for (int i = 0; i < n - 1; i++) sm += books[i];
    cout << (sm < books[n - 1] ? 2 * books[n - 1] : sm + books[n - 1]) << "\n";
	return 0;
}
