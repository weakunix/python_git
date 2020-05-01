hnd = { '1' : len('onehundred'),
        '2' : len('twohundred'),
        '3' : len('threehundred'),
        '4' : len('fourhundred'),
        '5' : len('fivehundred'),
        '6' : len('sixhundred'),
        '7' : len('sevenhundred'),
        '8' : len('eighthundred'),
        '9' : len('ninehundred'),
}

ten = { '2' : len('twenty'),
        '3' : len('thirty'),
        '4' : len('forty'),
        '5' : len('fifty'),
        '6' : len('sixty'),
        '7' : len('seventy'),
        '8' : len('eighty'),
        '9' : len('ninety'),
}

one = { '1' : len('one'),
        '2' : len('two'),
        '3' : len('three'),
        '4' : len('four'),
        '5' : len('five'),
        '6' : len('six'),
        '7' : len('seven'),
        '8' : len('eight'),
        '9' : len('nine'),
        '0' : 0
}

teen = { '10' : len('ten'),
         '11' : len('eleven'),
         '12' : len('twelve'),
         '13' : len('thirteen'),
         '14' : len('fourteen'),
         '15' : len('fifteen'),
         '16' : len('sixteen'),
         '17' : len('seventeen'),
         '18' : len('eighteen'),
         '19' : len('nineteen'),
}

ltot=0
for j in range(1,1000):
    i=str(j)
    l = 0
    if len(i)==3:
        l+=hnd[i[0]]
        if i[1:3]!="00":
            l+=3
        i=int(i)
        i=i%100
        i=str(i)
    if len(i)==2:
       if int(i[0])>1:
           l+=ten[i[0]]
           l+=one[i[1]]
       else:
           l+=teen[i]
    if len(i)==1:
        l+=one[i[0]]
    print("{} => {}".format(j, l))
    ltot += l
ltot+=len("onethousand")
print(ltot)
