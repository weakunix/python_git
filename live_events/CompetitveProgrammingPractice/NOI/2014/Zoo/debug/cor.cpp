#include <cstdio>
#include <cstring>

typedef long long LL;

const int MAXN = 1000005, MO = 1e9 + 7;

int n, fail[MAXN], num[MAXN];
LL ans;
char str[MAXN];

inline void calfail() {
    memset(fail, 0, sizeof(fail));
    memset(num, 0, sizeof(num));
    int i = 2, j = 0;
    num[1] = 1;
    for(; str[i]; i++) {
        while(j && str[j + 1] != str[i]) {
            j = fail[j];
        }
        if(str[j + 1] == str[i]) j++;
        fail[i] = j;
        num[i] = num[j] + 1;
    }
}

inline void match() {
    calfail();
    ans = 1;
    int i = 2, j = 0;
    for(; str[i]; i++) {
        while(j && str[j + 1] != str[i]) {
            j = fail[j];
        }
        if(str[j + 1] == str[i]) j++;
        while(j << 1 > i) j = fail[j];
        ans = ((num[j] + 1) * ans) % MO;
    }
}

int main() {
    scanf("%d", &n);
    while(n--) {
        scanf("%s", str + 1);
        match();
        printf("%lld\n", ans);
    }
    return 0;
}
