#imports
import numpy as np

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
         '**': lambda x, y: x ** y,
         '//': lambda x, y: x // y,
         'uniadd' : lambda x: x,
         'unisub' : lambda x: -x }
unio = { 'uniadd', 'unisub' } #uni operations
allf = { 'max' : max, #all functions
         'min' : min,
         'gcd' : gcd,
         'lcm' : lcm }
fargs = { 'max': [1, False], #required function argument amount [least amount, largest amount]
          'min': [1, False],
          'gcd': [1, False],
          'lcm': [1, False] }
precedence = { '+': 0, #precedence
               '-': 0,
               '*': 1,
               '/': 1,
               '//': 1,
               '^': 2,
               '**': 2,
               'uniadd' : 3,
               'unisub' : 3 }

#reverse polish calculation functions
##if string is a float
def is_number(s):
    try:
        return float(s)
    except:
        return False

##tokenize numbers and symbols
def tokenize(expr):
    tokenized = [] #tokenized expression
    dot = False #if there is a decimal point
    token_type = None #token type (number, operator
    token = '' #current token
    double_operator = False #if there is ** used for exponent or // used for floor
    for i in expr:
        if i in nums: #number
            if token_type == 'number':
                token += i
            else:
                tokenized.append(token)
                token = i
                token_type = 'number'
                dot = False
            if double_operator:
                double_operator = False
        elif (i in allo and i not in unio) or i == '(' or i == ')' or i == ',': #operator
            if double_operator == i:
                token += i
            else:
                tokenized.append(token)
                token = i
                token_type = 'operator'
                if i == '*' or i == '/':
                    double_operator = i
            dot = False
        elif i.isalpha(): #letter / function
            i = i.lower()
            if token_type == 'letter':
                token += i
            else:
                tokenized.append(token)
                token = i
                token_type = 'letter'
            dot = False
            if double_operator:
                double_operator = False
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
            if double_operator:
                double_operator = False
        elif i != ' ':
            print(f'\033[1;31;1mError: unrecognized token {i}')
            return None
        if '' in tokenized:
            tokenized.pop()
    tokenized.append(token)
    return tokenized

##shunting yard algorithm for shunting
def shunting(expr):
    operator = [] #operator stack
    output = [] #output stack
    function_arg = 0 #if a number is a function argument
    unioperator = True #if an operator is a unioperator
    operators_to_pop = [] #operators to pop from operator stack
    parentheses = 0 #number of parentheses
    for k, i in enumerate(expr):
        operators_to_pop = []
        if is_number(i): #number
            output.append(i)
            unioperator = False
        elif i in allo: #operator
            if unioperator:
                if i == '+':
                    i = 'uniadd'
                elif i == '-':
                    i = 'unisub'
                else:
                    print(f'\033[1;31;1mError: unrecognized unioperator {i}')
                    return None
            for j in range(1, len(operator) + 1):
                if operator[-j] == '(':
                    break
                try:
                    if (precedence[operator[-j]] >= precedence[i] and i not in unio) or precedence[operator[-j]] > precedence[i]:
                        operators_to_pop.append(-j)
                    else:
                        break
                except:
                    pass
            for l, j in enumerate(operators_to_pop):
                output.append(operator.pop(j + l))
            operator.append(i)
            unioperator = True
        elif i in allf: #function
            function_arg += 1
            operator.append('(')
            try:
                if expr[k + 2] == ')' and expr[k + 2] != ',':
                    operator.append([i, 0])
                else:
                    operator.append([i, 1])
                unioperator = False
            except:
                try:
                    if expr[k + 1] == '(':
                        print('\033[1;31;1mError: expected \')\' to end function')
                except:
                    print('\033[1;31;1mError: expected \'(\' when using function')
                return None
        elif i == '(': #start parentheses
            if expr[k - 1] not in allf:
                operator.append('(')
            parentheses += 1
            unioperator = True
        elif i == ')': #end parentheses
                for j in range(1, len(operator) + 1):
                    if operator[-j] == '(':
                        if type(operator[-j + 1]) == list:
                            function_arg -= 1
                        for l in range(j - 1):
                            output.append(operator.pop(-1))
                        operator.pop(-1)
                        break
                parentheses -= 1
                unioperator = False
        elif i == ',': #comma
            try:
                if expr[k + 1] != ')' and expr[k + 1] != ',':
                    for j in range(1, len(operator) + 1):
                        if type(operator[-j]) == list:
                            operator[-j][1] += 1
                            for l in range(j - 1):
                                output.append(operator.pop(-1))
                            break
                unioperator = True
            except:
                print('\033[1;31;1mError: expected \')\' to end function')
        else:
            print(f'\033[1;31;1mErorr: unrecognized token {i}')
            return None
    if parentheses > 0:
        print('\033[1;31;1mError: expected \')\'')
        return None
    if parentheses < 0:
        print('\033[1;31;1mError: unexpected \')\'')
        return None
    for i in range(len(operator)):
        output.append(operator.pop(-1))
    return output

##evaluate reverse polish expression
def eval_rp(expr):
    numstack = [] #number stack
    operator = '' #operator / function
    for i in expr:
        if type(i) == list: #function
            min_args = fargs[i[0]][0]
            max_args = fargs[i[0]][1]
            if min_args > i[1]:
                print(f'\033[1;31;1mError: function \'{i}\' must contain at least {min_args} arguments')
                return None
            if max_args and max_args < i[1] :
                print(f'\033[1;31;1mError: function \'{i}\' must not contain more than {max_args} arguments')
                return None
            funcargs = []
            for k in range(i[1]):
                funcargs.append(numstack.pop(-1))
            funcargs.reverse()
            numstack.append(allf[i[0]](*funcargs))
        elif i in unio: #uni operator
            numstack.append(allo[i](numstack.pop()))
        elif i in allo: #operator
            oargs = [numstack.pop(), numstack.pop()]
            oargs.reverse()
            numstack.append(allo[i](*oargs))
        else: #number
            numstack.append(float(i))
    if len(numstack) != 1:
        print('\033[1;31;1mError: invalid expression')
        return None
    return numstack[0]
           
#console functions 
##evaluate input
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
        if tokenize(inpt) != None:
            if shunting(tokenize(inpt)) != None:
                if eval_rp(shunting(tokenize(inpt))) != None:
                    print(f'\033[1;32;1m{eval_rp(shunting(tokenize(inpt)))}')
       
#main
if __name__ == '__main__':
    print('\033[1;32;1mWelcome to the Cowculator v1.0!\033[0m')
    while True:
        eval_input()
