cl=1
n=0
cn=0
for i in range(2, 1000000):
    print("trying {}".format(i))
    l=1
    n=i
    while i!=1:
        if i%2==0:
            i=i/2
        else:
            i=3*i+1
        l+=1
    if l>cl:
        cl=l
        cn=n
print(cn)
