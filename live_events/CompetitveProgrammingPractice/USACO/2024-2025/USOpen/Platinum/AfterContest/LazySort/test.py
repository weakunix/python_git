cnt = 0
all1 = []
for i in range(0, 11):
    for j in range(0, 11):
        for k in range(0, 11):
            l = [1, i, 3, j, k, 5]
            o = [1, i, 3, j, k, 5]
            
            prvo = []
            while prvo != o:
                prvo = o.copy()
                for a in range(5):
                    while o[a] > o[a + 1]:
                        o[a] -= 1
                        o[a + 1] += 1

            if o == sorted(l):
                cnt += 1
                all1.append(l)
                
print(cnt)




for i in range(1, 11):
    for j in range(1, 11):
        for k in range(1, 11):
            l = [1, i, 5, j, k, 10]
            works = True
            eq = False
            for a in range(5):
                if l[a + 1] < l[a] or (l[a + 1] == l[a] and eq):
                    works = False
                if l[a + 1] == l[a]:
                    eq = True
                else:
                    eq = False
            if works:
                l2 = [i - j for j, i in enumerate(l)]
                if l2 not in all1:
                    print(l, l2)
