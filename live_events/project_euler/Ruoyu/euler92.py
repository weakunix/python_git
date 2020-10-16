#vars
lead_to_89 = []
lead_to_1 = []

#testing all numbers from 1 to 10 ** 7
if __name__ == '__main__':
    for i in range(1, 10 ** 7):
        original = i
        print(i)
        while True:
            if i in lead_to_89 or i == 89:
                lead_to_89.append(original)
                break
            elif i in lead_to_1 or i == 1:
                lead_to_1.append(original)
                break
            else:
                i = sum([int(k) ** 2 for k in str(i)])
    print(len(lead_to_89))
