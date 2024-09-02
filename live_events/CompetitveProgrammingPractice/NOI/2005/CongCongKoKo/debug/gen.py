import random

n = 20
m = 35

e = []

adj = [[] for i in range(n + 1)]
vis = []

def dfs(node):
    global adj, vis
    vis.append(node)
    for i in adj[node]:
        if i not in vis:
            dfs(i)

for i in range(m):
    a = random.randint(1, n - 1)
    b = random.randint(a + 1, n)
    cur = (a, b)
    while cur in e:
        a = random.randint(1, n)
        b = random.randint(a, n)
        cur = (a, b)
    e.append(cur)
    adj[cur[0]].append(cur[1])
    adj[cur[1]].append(cur[0])

stc = random.randint(1, n)
dfs(stc)
stm = random.choice(vis)

print(n, m)
print(stc, stm)
for i in e:
    print(i[0], i[1])
