#imports
import numpy as np, sympy

#user def albreto functions
##gcd for any amount of numbers
def gcd(*args):
    if len(args) == 0:
        print('\033[1;31;1mError: gcd/gcf funtion must contain at least 1 argument')
        return None
    elif len(args) == 1:
        return args[0]
    elif len(args) == 2:
        return gcd_for_two(args[0], args[1])
    else:
        gcd_of_all = args[0]
        for i in args:
            gcd_of_all = gcd_for_two(gcd_of_all, i)
        return gcd_of_all

##gcd for two numbers
def gcd_for_two(x, y):
    while x != 0 and y != 0:
        x %= y
        if x == 0:
            return y
        y %= x
        if y == 0:
            return x

##lcm for any amount of numbers
def lcm(*args):
    if len(args) == 0:
        print('\033[1;31;1mError: lcm funtion must contain at least 1 argument')
        return None
    elif len(args) == 1:
        return args[0]
    elif len(args) == 2:
        return lcm_for_two(args[0], args[1])
    else:
        lcm_of_all = args[0]
        for i in args:
            lcm_of_all = lcm_for_two(lcm_of_all, i)
        return lcm_of_all

##lcm for two numbers
def lcm_for_two(x, y):
    return x * y / gcd_for_two(x, y)

#vars
inpt = '' #user input
modes = { 0: 'arithmetic', #modes
          1: 'algebra',
          2: 'fractions',
          3: 'bases' }
current_mode = 0
nums = [str(i) for i in range(10)] #all numbers
allo = { '+': lambda x, y: x + y, #all operators
         '-': lambda x, y: x - y,
         '*': lambda x, y: x * y,
         '/': lambda x, y: x / y,
         '^': lambda x, y: x ** y,
         'uniadd' : lambda x: x,
         'unisub' : lambda x: -x }
unio = { 'uniadd', 'unisub' } #uni operations
allf = { 'max' : max, #all functions
         'min' : min,
         'gcd' : gcd,
         'lcm' : lcm }
pr = { '+': 0, #order of operations
       '-': 0,
       '*': 1,
       '/': 1,
       '^': 2,
       'uniadd' : 3,
       'unisub' : 3 }

#reverse polish calculation functions
##tokenize numbers and symbols
def tokenize(expr):
    tokenized = [] #tokenized expression
    dot = False #if there is a decimal point
    token_type = None #token type (number, operator
    token = '' #current token
    for k, i in enumerate(expr):
        if i in nums: #number
            if token_type == 'number':
                token += i
            else:
                tokenized.append(token)
                token = i
                token_type = 'number'
                dot = False
        elif (i in allo and i not in unio) or i == '(' or i == ')' or i == ',': #operator
            tokenized.append(token)
            token = i
            token_type = 'operator'
            dot = False
        elif i.isalpha(): #letter / function
            if token_type == 'letter':
                token += i
            else:
                tokenized.append(token)
                token = i
                token_type = 'letter'
            dot = False
        elif i == '.': #decimal point
            if dot:
                print(f'\033[1;31;1mError: {token} contains more than one decimal point')
                return None
            else:
                if token_type == 'number':
                    token += i
                else:
                    tokenized.append(token)
                    token = i
                    token_type = 'number'
                dot = True
        elif i != ' ':
            print(f'\033[1;31;1mError: unrecognized token {i}')
            return None
        if '' in tokenized:
            tokenized.pop()
        if k == len(expr) - 1:
            tokenized.append(token)
    return tokenized

#console functions 
##evaluaate input
def eval_input():
    global current_mode, modes
    inpt = input('\n' + '\033[1;36;1m=' * 50 + f'\033[1;32;1m\n\nCommands:\n\n\033[1;33;1mFunctions: List functions of {modes[current_mode]} mode\n\033[1;34;1mModes: Shows your current mode and all modes of the Cowculator\n\033[1;36;1mSwitch [mode]: Switch to selected mode\n\033[1;31;1mExit: Exit program\n\n\033[0mTo calculate just type in a valid equation:\n').strip(' ')
    if inpt.lower() == 'exit':
        inpt = input('\n' + '\033[1;36;1m=' * 50 + '\033[1;31;1m\n\nAre you sure you want to exit?\n\033[0m')
        try:
            inpt = inpt[0].lower()
        except:
            inpt = None
        if inpt == 'y':
            raise SystemExit('\033[0m')
    elif 'switch' in inpt.lower():
        switchable = True
        inpt = inpt.lower().strip(' ').strip('switch').strip(' ')
        try:
            if inpt[:2] == 'ar':
                current_mode = 0
            elif inpt[:2] == 'al':
                current_mode = 1
            elif inpt[0] == 'f':
                current_mode = 2
            elif inpt[0] == 'b':
                current_mode = 3
            else:
                print(f'\033[1;31;1mError: mode {inpt} not found')
                switchable = False
        except:
            print('\033[1;31;1mError: please specify which mode you would like to change to')
            switchable = False
        if switchable:
            print('\n' + '\033[1;36;1m=' * 50 + f'\n\nSwitched to {modes[current_mode]} mode')
    elif inpt.lower() == 'functions':
        print('\n' + '\033[1;36;1m=' * 50 + '\033[1;33;1m\n\nToo lazy, haven\'t logged the functions yet')
    elif inpt.lower() == 'modes':
        print('\n' + '\033[1;36;1m=' * 50 + f'\033[1;34;1m\n\nCurrent mode: {modes[current_mode]}\n\nAll modes:')
        for i in range(4):
            print(modes[i][0].upper() + modes[i][1:])
    else:
        if current_mode == 0:
            calculate_arithmetic(inpt)
       
#main
if __name__ == '__main__':
    print('\033[1;32;1mWelcome to the Cowculator v1.0!\033[0m')
    while True:
        eval_input()
