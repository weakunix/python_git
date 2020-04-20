sqaure = 0
s = 0
s2 = 0
for i in range(1, 101):
    square = i * i
    s = s + square
for x in range(1, 101):
    s2 = s2 + x
s2 = s2 * s2
ans = s2 - s 
print(ans)
