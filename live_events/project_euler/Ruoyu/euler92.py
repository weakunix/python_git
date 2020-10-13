#vars
lead_to_89 = []
lead_to_1 = []

#user def functions
##sum of the square of digits of a number
def digit_square_sum(x):
    dss = 0
    for i in str(x):
        dss += int(i) ** 2
    return dss

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
            break
    print(len(lead_to_89))
