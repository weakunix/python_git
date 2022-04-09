#vars
text = ''
ascii_sum = 0

#reading text
with open('decrypted57.txt', 'r') as decrypted:
    text = decrypted.readlines()
text = text[0].strip('\n')

#final answer after human deduction
for i in text:
    ascii_sum += ord(i)
print(ascii_sum)
