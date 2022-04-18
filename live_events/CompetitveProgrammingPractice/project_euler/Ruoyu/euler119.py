
#Vars
Seq = set() #Set of sequence of an
Possible = [] #Possible an in the form (n ^ m, n)
Powers = {2: 2} #Dict of powers n: n^m where m is maximized and n^m <= the latest n squared
n = 2 #n

#User def functions
def DigitSum(n) -> int:
    count = 0
    for i in str(n):
        count += int(i)
    return count

#Main
if __name__ == '__main__':
    while len(Seq) < 30:
        n += 1
        Powers[n] = n
        mxtv = n ** 2
        for i in Powers:
            tv = i * Powers[i]
            while tv <= mxtv:
                Possible.append((tv, i))
                Powers[i] = tv
                tv *= i
        for i in Possible:
            if i[0] >= 10 and DigitSum(i[0]) == i[1]:
                Seq.add(i[0])
                print(len(Seq), n)
    Seq = list(Seq)
    Seq.sort()
    print(Seq)
