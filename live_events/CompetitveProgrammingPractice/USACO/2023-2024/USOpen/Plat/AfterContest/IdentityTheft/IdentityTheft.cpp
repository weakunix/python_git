#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

struct Node {
    int state, ht; //0: unused leaf, 1: used leaf, 2: used non-leaf
    Node* child[2];

    Node(int s, int h) : state(s), ht(h) {}

    ~Node() {}
};

int n, ans = 0;
map<string, int> cnt;
Node* rt = new Node(0, 0);

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        cnt[s]++;
    }

    for (auto it = cnt.rbegin(); it != cnt.rend(); it++) {
        int sz = it->first.size();
        Node* cur = rt;
        for (char c : it->first) {
            assert(cur->state != 1);
            if (not cur->state) {
                cur->state = 2;
                cur->child[0] = new Node(0, cur->ht + 1);
                cur->child[1] = new Node(0, cur->ht + 1);
            }
            cur = cur->child[c - '0'];
        }
        
        int curcnt = it->second;
        queue<Node*> q1, q2;
        q1.push(cur);

        while (curcnt) {
            Node *a = (q1.empty() ? nullptr : q1.front()), *b = (q2.empty() ? nullptr : q2.front());
            assert(a or b);

            if (not a or (b and b->ht <= a->ht - 2)) {
                q2.pop();
                curcnt--;

                ans += b->ht + 2 - sz;

                b->state = 2;
                b->child[0] = new Node(1, b->ht + 1);
                b->child[1] = new Node(1, b->ht + 1);
                q2.push(b->child[0]);
                q2.push(b->child[1]);
            }
            else {
                q1.pop();

                if (a->state == 2) {
                    q1.push(a->child[0]);
                    q1.push(a->child[1]);
                    continue;
                }

                if (not a->state) {
                    curcnt--;

                    ans += a->ht - sz;
                    a->state = 1;
                }

                q2.push(a);
            }
        }
    }

    cout << ans << "\n";

	return 0;
}
