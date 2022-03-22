
#Vars
PrevPalinCount = {0: (0, 1), 1: (0, 1)} #Dict of previous palindrome counts in form (twopal, total)
n = 1 #n
M = 0 #M
Mil = 10 ** 6

#User def functions
def AddNewPalinCount(x) -> None:
    global Mil
    count = 0
    for i in range(1, x + 1):
        if i == 2:
            count += PrevPalinCount[x - i][1]
        else:
            count += PrevPalinCount[x - i][0]
    PrevPalinCount[x] = (count % Mil, 2 ** (x - 1) % Mil)
    return
    

#Main
if __name__ == '__main__':
    while True:
        n += 1
        M = n % 2
        count = 0
        while M <= n:
            temp = (n - M) // 2
            try:
                temp = PrevPalinCount[temp]
                if M == 2:
                    count += temp[1]
                else:
                    count += temp[0]
            except:
                AddNewPalinCount(temp)
                temp = PrevPalinCount[temp]
                if M == 2:
                    count += temp[1]
                else:
                    count += temp[0]
            M += 2
        count %= Mil
        print(n, count)
        if count == 0 and n > 42:
            print(n)
            break
