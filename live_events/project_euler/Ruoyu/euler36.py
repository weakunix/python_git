#vars
sumn = 0

#user def functions
#check for palindrome
def is_palindrome(x):
    x = str(x)
    for i in range(len(x)):
        if x[i] != x[len(x) - i - 1]:
            return False
    return True

#convert to binary
def convert_to_binary(x):
    num = ''
    for i in range(20):
        num = str(x & 1) + num
        x >>= 1
    return int(num)

#looking for double base palindromes
for i in range(1, 1000000):
    if is_palindrome(i):
         if is_palindrome(convert_to_binary(i)):
             sumn += i
             print(i, convert_to_binary(i))
print(sumn)
