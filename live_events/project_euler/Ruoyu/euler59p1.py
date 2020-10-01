#vars
encrypted = '' #encryped ASCII
decrypted = [] #decrypted ASCII
text = '' #decrypted text
cipher = [] #cipher

#get encryped text
with open('p059_cipher.txt', 'r') as ciphered_text:
    encrypted = ciphered_text.readline()
encrypted = [int(i) for i in encrypted.split(',')]

#testing all three lower case letter keys
for i in range(ord('a'), ord('z') + 1):
    for j in range(ord('a'), ord('z') + 1):
        for k in range(ord('a'), ord('z') + 1):
            cipher = [i, j, k]
            decrypted = []
            for n, c in enumerate(encrypted):
                decrypted.append(c ^ cipher[n % 3])
            if sum([1 for i in decrypted if i == ord(' ')]) >= 140:
                text = ''
                for l in decrypted:
                    text += chr(l)
                print(text)
