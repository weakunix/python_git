#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <complex>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

typedef long long ll;
typedef complex<double> cd;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int L = 1 << 19;
const double pi = acos(-1);

int n;
string s;
vector<cd> p1(L), p2(L);

void fft(vector<cd>& a, bool inv) {
    int len = a.size();
    if (len == 1) return;

    vector<cd> a1(len / 2), a2(len / 2);
    for (int i = 0; i < len / 2; i++) {
        a1[i] = a[2 * i];
        a2[i] = a[2 * i + 1];
    }
    
    fft(a1, inv);
    fft(a2, inv);

    double theta = 2 * pi / len * (inv ? -1 : 1);
    cd w(1), wn(cos(theta), sin(theta));
    for (int i = 0; i < len / 2; i++) {
        a[i] = a1[i] + w * a2[i];
        a[i + len / 2] = a1[i] - w * a2[i];
        if (inv) {
            a[i] /= 2;
            a[i + len / 2] /= 2;
        }
        w *= wn;
    }

    return;
}

int main() {
    cin >> s;
    n = s.size();
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') continue;
        p1[i] = 1;
        p2[n - i - 1] = 1;
    }

    fft(p1, false);
    fft(p2, false);
    for (int i = 0; i < L; i++) p1[i] *= p2[i];
    fft(p1, true);

    for (int i = n - 2; i >= 0; i--) cout << (int) round(p1[i].real()) << " ";
    cout << "\n";

	return 0;
}
