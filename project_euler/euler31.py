#vars
count = 0
total = []

#testing each amount of coins to see if they are 2 pounds
for onep in range(0, 3):
    for fifty in range(0, 5):
        for twenty in range(0, 11):
            for ten in range(0, 21):
                for five in range(0, 41):
                    for two in range(0, 101):
                        total = sum([100 * onep, 50 * fifty, 20 * twenty, 10 * ten, 5 * five, 2 * two])
                        if total <= 200:
                            count += 1
                            print([100 * onep, 50 * fifty, 20 * twenty, 10 * ten, 5 * five, 2 * two], total)
                        if total == 200:
                            break
print(count + 1)
