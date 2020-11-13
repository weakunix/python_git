#imports
import random

#vars
name = '' #name

#user def functions
##encrypt and decrypt password
def encrypt_decrypt(password, encrypt):
    ciphered_password = ''
    if encrypt:
        cipher = ''
        for _ in range(len(password)):
            letter = random.randint(0, 1)
            if letter:
                cipher += chr(random.randint(ord('A'), ord('Z')))
            else:
                cipher += chr(random.randint(ord('a'), ord('z')))
    else:
        cipher = password[int(len(s) / 2) / 2:]
        password = password[:int(len(s) / 2)]
    for i in range(len(password)):
        ciphered_password = chr(ord(password[i]) ^ ord(cipher[i]))
    if encrypt:
        return ciphered_password + cipher
    return ciphered_password

##login
def login():
    names = []
    passwords = []
    with open('./modes/airplane_data/names.txt', 'r') as name_file:
        for name in name_file:
            names.append(name.strip('\n'))
    with open('./modes/airplane_data/passwords.txt', 'r') as password_file:
        for password in password_file:
            passwords.append(password.strip('\n'))
    inpt = input('\033[1;34;1m(L)ogin: Login to current account\n\033[1;35;1m(S)ign Up: Make a new account\n\033[1;31;1mE(x)it: Exit game\n\n\033[0mChoose a command:\n').lower()
    try:
        if inpt != 'exit':
            inpt = inpt[0]
    except:
        pass
    if inpt == 'l':
        name = input('\n' + '\033[1;36;1m=' * 50 + '\n\n\033[1;34;1mName: \033[0m')
        try:
            password = encrypt_decrypt(passwords[names.index(name)], False)
            inpt = input('\033[1;34;1mPassword: \033[0m')
            if inpt == password:
                print('\n' + '\033[1;36;1m=' * 50 + f'\033[1;32;1mLogged in as {name}\n')
                return name
            else:
                print('\n' + '\033[1;36;1m=' * 50 + f'\n\n\033[1;31;1mInccorect password\n')
        except:
            print('\n\033[1;31;1mAccount not found\n')
            return None
    elif inpt == 's':
        name = input('\n' + '\033[1;36;1m=' * 50 +'\n\n\033[1;35;1mName: \033[0m')
        if name in names:
            print('\n'
    elif inpt == 'x' or inpt == 'exit':
        return False
    else:
        print('\033[1;31;1mInvalid command\n')

##game
def game():
    print('\033[1;32;1mWelcome to the Airplane Game!\n')
    while True:
        print('\033[1;36;1m=' * 50 + '\n')
        name = login()
        if name == False or name:
            break
    while True:
        if not name:
            break
