n = int(input())
s = [input() for i in range(n)]
d = [set() for i in range(n)]
alld = {}


for i in range(n):
    for j in range(len(s[i])):
        for k in range(j, len(s[i])):
            d[i].add(s[i][j:k + 1])

for i in range(n):
    for j in d[i]:
        try:
            alld[j] += 1
        except:
            alld[j] = 1

for i in range(n):
    ans = 0
    for j in d[i]:
        ans += (alld[j] == 1)
    print(ans)
