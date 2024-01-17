import random

h = 20
w = 10
n = 10
st = [i for i in range(1, h + 1)]

with open('test.in', 'w') as fi:
    print(h, w, n)
    fi.write(f'{h} {w} {n}\n')

    for i in range(n):
        u = random.choice(st)
        l = random.randint(1, w)
        if l == 1:
            r = random.randint(l, w - 1)
        else:
            r = random.randint(l, w)
        s = random.randint(0, h)
        st.remove(u)
        print(u, l, r, s)
        fi.write(f'{u} {l} {r} {s}\n')
