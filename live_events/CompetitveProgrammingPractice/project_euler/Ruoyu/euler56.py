#vars
mds = [0, 0] #maximum digit sum

#user def functions
##digit sum
def digit_sum(num):
    num = str(num)
    digit_sum = 0
    for i in num:
        digit_sum += int(i)
    return digit_sum

if __name__ == '__main__':
    for a in range(1, 100):
        for b in range(1, 100):
            print(digit_sum(a ** b))
            if digit_sum(a ** b) > mds[0]:
                mds = [digit_sum(a ** b), a, b]
    print(mds)
