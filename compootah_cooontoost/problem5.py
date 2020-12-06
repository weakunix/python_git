a = 16
b = 2
c = 4 
d = 0 
e = 5 

if a < b:
    a += b
else:
    a -= b

if a*d < c*d:
    a += d
else:
    c = c+e

if b**d == 1:
    d += 1
else:
    b += 1    

if int(a/c) == a/c:
    a = a/c 
else:
    a -= c

if (a < e) or (b>=d):
    a = e
else:
    b=d

if (b>= c) and (d<=e):
    c = b-c 
else:
    d = a-e

print(a**d + b * e/a-c*(a/e+b**b))