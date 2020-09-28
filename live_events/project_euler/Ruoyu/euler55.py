#vars
count = [] #total lychrel numbers

#user def functions
##test if a number is a palindrome
def is_palindrome(x):
    x = str(x)
    for i in range(len(x) // 2):
        if x[i] != x[-(i + 1)]:
            return False
    return True

#flip a number
def flip_num(x):
    x = str(x)
    flipped = ''
    for i in range(1, len(x) + 1):
        flipped += x[-i]
    return int(flipped)

#testing all numbers from 1 to 10000 to find total amount of lychrel numbers
if __name__ == '__main__':
    for i in range(1, 10 ** 4 + 1):
        original_num = i
        lychrel = True
        for k in range(50):
            i += flip_num(i)
            if is_palindrome(i):
                lychrel = False
                break
        if lychrel:
            count.append(original_num)
    print(f'{count}\n\n{len(count)}')
