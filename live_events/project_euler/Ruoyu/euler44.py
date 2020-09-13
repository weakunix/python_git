#imports
import datetime as dt

#starting time
start_time = dt.datetime.now()

#vars
pentagonals = [1, 5] #pentagonal numbers (starting off with the first two)
count = 2 #which pentagonal number we are on
done = False

#find two pentagonal numbers who's sum and difference are pentagonal
while True:
    count += 1 #add 1 to count
    pentnum = int(count * (3 * count - 1) / 2) #this is the countth pentagonal number
    print(count)
    for i in pentagonals:
        if pentnum - i in pentagonals: #if two pentagonal numbers sum to a pentagonal number
            dif = pentnum - 2 * i #difference of two pentagonal numbers
            if dif < 0: #if the difference is 
                dif = -dif
            if dif in pentagonals:
                print(dif)
                done = True
                break
    if done:
        print((dt.datetime.now() - start_time).total_seconds())
        break
    pentagonals.append(pentnum)
