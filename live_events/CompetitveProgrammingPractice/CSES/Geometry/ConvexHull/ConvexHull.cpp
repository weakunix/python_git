#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <complex>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef complex<ll> pt;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define x real()
#define y imag()

const int N = 2e5;

int n;
pt arr[N];
vector<pt> top, bot;

bool cmp1(pt a, pt b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool cmp2(pt a, pt b) {
    return a.x == b.x ? a.y > b.y : a.x > b.x;
}

void cinpt(pt& p) {
	int curx, cury;
	cin >> curx >> cury;
	p = {curx, cury};
	return;
}

ll cross(pt a, pt b) {
	return (conj(a) * b).y;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cinpt(arr[i]);

    sort(arr, arr + n, cmp1);
    bot = {arr[0], arr[1]};
    for (int i = 2; i < n; i++) {
        while (bot.size() > 1 and cross(bot.back() - bot[bot.size() - 2], arr[i] - bot[bot.size() - 2]) < 0) bot.pop_back();
        bot.push_back(arr[i]);
    }
    bot.pop_back();

    sort(arr, arr + n, cmp2);
    top = {arr[0], arr[1]};
    for (int i = 2; i < n; i++) {
        while (top.size() > 1 and cross(top.back() - top[top.size() - 2], arr[i] - top[top.size() - 2]) < 0) top.pop_back();
        top.push_back(arr[i]);
    }
    top.pop_back();
    
    cout << bot.size() + top.size() << "\n";
    for (pt p : bot) cout << p.x << " " << p.y << "\n";
    for (pt p : top) cout << p.x << " " << p.y << "\n";

	return 0;
}
