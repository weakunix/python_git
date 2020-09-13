import math

def mandle(a,b,c,d,n):
    real = c**2-d**2+a
    img = 2*c*d+b
    c=real
    d = img
    if n>1 and distance(c,d) < 2:
        return mandle(a,b,c,d,n-1)
    else:
        return(c,d)

def distance(a,b):
    try:
        return math.sqrt(a**2+b**2)
    except:
        return 2
