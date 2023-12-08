n, m = map(int, input().split())
s = input()

for i in range(m):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    
    s = s[:a] + s[a:b+1][::-1] + s[b+1:]

print(s)
