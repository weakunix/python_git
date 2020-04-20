#vars

prod=1
s=0

for i in range(1, 1001):
    prod*=2
prod=str(prod)
for k in prod:
    s+=int(k)
print(s)
