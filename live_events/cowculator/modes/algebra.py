#imports
import collections, math

#user def functions
##gcd for any amount of numbers
def gcd(*args):
    list_of_ans = [] #list of answers
    for i in args:
        if type(i) == list:
            pass #TODO CODE THIS
    if len(args) == 1:
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
    if len(args) == 1:
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

##factorial
def factorial(x):
    prod = 1
    for i in range(1, x + 1):
        prod *= i
    return prod

##double factorial
def double_factorial(x):
    prod = 1
    for i in range(x % 2, x + 1, 2):
        if i != 0:
            prod *= i
    return prod

##ceiling
def ceiling(x):
    if int(x) == x:
        return int(x)
    return int(x) + 1

##previous answers
def ans(x = -1, y = 'all'):
    answers = []
    with open('./answers.txt', 'r') as answer_file:
        for line in answer_file:
            if line.strip('\n') != '':
                line = line.strip('\n').split(' ')
                for i in range(len(line)):
                    line[i] = float(line[i])
                answers.append(line)
    try:
       if x == int(x):
           x = int(x)
       else:
           print(f'\033[1;31;1mError: invalid ans index {x}')
           return None
    except:
        print(f'\033[1;31;1mError: invalid ans index {x}')
        return None
    if type(y) == float or type(y) == int:
        try:
            if y == int(y):
                y = int(y)
            else:
                print(f'\033[1;31;1mError: invalid ans index {y}')
                return None
        except:
            print(f'\033[1;31;1mError: invalid ans index {y}')
            return None
    else:
        y = y.lower()
        if y != 'all':
            print(f'\033[1;31;1mError: invalid ans index {y}')
    if x == 0 or y == 0:
        print('\033[1;31;1mError: ans index must not be 0')
        return None
    try:
        if x > 0:
            previous_answer = answers[x - 1]
        else:
            previous_answer = answers[x]
    except:
        print(f'\033[1;31;1mError: answer {x} does not exist')
        return None
    if y == 'all':
        if len(previous_answer) == 1:
            return previous_answer[0]
        return previous_answer
    else:
        try:
            if y > 0:
                previous_answer = previous_answer[y - 1]
            else:
                previous_answer = previous_answer[y]
        except:
            print(f'\033[1;31;1mError: index {y} of answer {x} does not exist')
            return None
    return previous_answer

##prime factorization
def prime_factorization(x):
    try:
        if int(x) == x:
            x = int(x)
        else:
            print(f'\033[1;31;1mError: {x} is not an integer')
            return None
    except:
        print(f'\033[1;31;1mError: {x} is not an integer')
        return None
    prime_factors = []
    for i in range(2, x + 1):
        while x % i == 0:
            x /= i
            prime_factors.append(i)
    if len(prime_factors) == 1:
        return prime_factors[0]
    return prime_factors

##mean
def mean(*args):
    return sum(args) / len(args)

##median
def median(*args):
    args = list(args)
    args.sort()
    if len(args) % 2 == 0:
        return (args[len(args) / 2] + args[len(args) / 2 - 1]) / 2
    return args[int((len(args) - 1) / 2)]

##mode
def mode(*args):
    amount_of_numbers = collections.Counter()
    largest_occurence = 0
    mode_nums = []
    for i in args:
        amount_of_numbers[i] += 1
    for i in amount_of_numbers:
        if amount_of_numbers[i] > largest_occurence:
            largest_occurence = amount_of_numbers[i]
    for i in amount_of_numbers:
        if amount_of_numbers[i] == largest_occurence:
            mode_nums.append(i)
    if len(mode_nums) == 1:
        return mode_nums[0]
    return mode_nums

##factors of number
def factorize(x):
    try:
        if int(x) == x:
            x = int(x)
        else:
            print(f'\033[1;31;1mError: {x} is not an integer')
            return None
    except:
        print(f'\033[1;31;1mError: {x} is not an integer')
        return None
    factors = []
    for i in range(1, x + 1):
        if i in factors:
            factors.sort()
            return factors
        if x % i == 0:
            factors.append(i)
            factors.append(int(x / i))

##logarithm
def log(*args):
    args = list(args)
    if args[0] <= 1:
        print('\033[1;31;1mError: log base must be greater than 1')
        return None
    if args[-1] <= 0:
        print('\033[1;31;1mError: log argument must be greater than 0')
        return None
    if len(args) == 2:
        args.reverse()
    return math.log(*args)

#vars
nums = [str(i) for i in range(10)] #all numbers
allo = { '+': lambda x, y: x + y, #all operators
         '-': lambda x, y: x - y,
         '*': lambda x, y: x * y,
         '/': lambda x, y: x / y,
         '^': lambda x, y: x ** y,
         '**': lambda x, y: x ** y,
         '//': lambda x, y: x // y,
         '√': lambda x: x ** (1 / 2),
         '%': lambda x, y: x % y,
         'uniadd' : lambda x: x,
         'unisub' : lambda x: -x,
         '!': lambda x, y: factorial(x),
         '!!': lambda x, y: double_factorial(x) }
unio = {'uniadd', 'unisub', '√'} #uni operations
allf = { 'max': max, #all functions
         'min': min,
         'gcd': gcd,
         'gcf': gcd,
         'lcm': lcm,
         'mean': mean,
         'median': median,
         'mode': mode, 
         'root': lambda x, y: y ** (1 / x),
         'floor': lambda x: int(x),
         'ceiling': ceiling,
         'abs': abs,
         'ans': ans,
         'log': log,
         'factorize': factorize,
         'prime_factorize': prime_factorization,
         'pf': prime_factorization }
fargs = { 'max': [1, False], #required function argument amount [least amount, largest amount]
          'min': [1, False],
          'gcd': [1, False],
          'gcf': [1, False],
          'lcm': [1, False],
          'mean': [1, False],
          'median': [1, False],
          'mode': [1, False], 
          'root': [2, 2],
          'floor': [1, 1],
          'ceiling': [1, 1],
          'abs': [1, 1],
          'ans': [0, 2],
          'log': [1, 2], 
          'factorize': [1, 1],
          'prime_factorize': [1, 1],
          'pf': [1, 1] }
precedence = { '+': 0, #precedence
               '-': 0,
               '*': 1,
               '/': 1,
               '//': 1,
               '^': 2,
               '**': 2,
               '√': 2,
               'uniadd' : 3,
               'unisub' : 3,
               '!': 4,
               '!!': 4 }

#reverse polish calculation functions
##if string is a float
def is_number(s):
    try:
        return float(s)
    except:
        return None

##tokenize numbers and symbols
def tokenize(expr):
    tokenized = [] #tokenized expression
    dot = False #if there is a decimal point
    token_type = None #token type (number, operator
    token = '' #current token
    double_operator = False #if there is ** used for exponent or // used for floor
    for i in expr:
        if i in nums: #number
            if token_type == 'number' or token_type == 'letter':
                token += i
            else:
                tokenized.append(token)
                token = i
                token_type = 'number'
                dot = False
            if double_operator:
                double_operator = False
        elif i in allo or i == '(' or i == ')' or i == ',': #operator
            if double_operator == i:
                token += i
                double_operator = False
            else:
                tokenized.append(token)
                token = i
                token_type = 'operator'
                if i == '*' or i == '/' or i == '!':
                    double_operator = i
            dot = False
        elif i.isalpha() or i == '_': #letter / function
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
            print(f'\033[1;31;1mError: unrecognized token \'{i}\'')
            return None
        if '' in tokenized:
            tokenized.pop()
        try:
            if tokenized[-1] == '!' or tokenized[-1] == '!!':
                tokenized.append('0')
        except:
            pass
    tokenized.append(token)
    try:
        if tokenized[-1] == '!' or tokenized[-1] == '!!':
            tokenized.append('0')
    except:
        pass
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
        if is_number(i) != None: #number
            output.append(i)
            unioperator = False
        elif i in allo: #operator
            if unioperator:
                if i == '+':
                    i = 'uniadd'
                elif i == '-':
                    i = 'unisub'
                elif i != '√':
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
        elif i.lower() == 'all':
            valid_all = False
            for j in range(1, len(operator) + 1):
                if type(operator[-j]) == list:
                    if operator[-j][0] == 'ans':
                        output.append(i)
                        unioperator = False
                        valid_all = True
                    else:
                        print(f'\033[1;31;1mErorr: unrecognized token \'{i}\'')
                        return None
            if not valid_all:
                print(f'\033[1;31;1mErorr: unrecognized token \'{i}\'')
                return None
        else:
            print(f'\033[1;31;1mErorr: unrecognized token \'{i}\'')
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
        if type(i) == list and i[0] in allf: #function
            min_args = fargs[i[0]][0]
            max_args = fargs[i[0]][1]
            if min_args > i[1]:
                print(f'\033[1;31;1mError: function \'{i[0]}\' must contain at least {min_args} arguments')
                return None
            if max_args and max_args < i[1] :
                print(f'\033[1;31;1mError: function \'{i[0]}\' must not contain more than {max_args} arguments')
                return None
            funcargs = []
            for k in range(i[1]):
                funcargs.append(numstack.pop(-1))
            funcargs.reverse()
            numstack.append(allf[i[0]](*funcargs))
            if numstack[-1] == None:
                return None
        elif i in unio: #uni operator
            numstack.append(allo[i](numstack.pop()))
        elif i in allo: #operator
            oargs = [numstack.pop(), numstack.pop()]
            oargs.reverse()
            if i == '!' or i == '!!':
                if int(oargs[0]) != oargs[0]:
                    return None
                oargs[0] = int(oargs[0])
            numstack.append(allo[i](*oargs))
        elif i == 'all': #all parameter
            numstack.append(i)
        else: #number
            numstack.append(float(i))
    if len(numstack) != 1:
        print('\033[1;31;1mError: invalid expression')
        return None
    return numstack[0]
          
#testing
if __name__ == '__main__':
    with open('./../answers.txt', 'w') as answers:
        answers.write('')
    while True:
        inpt = input('\033[0mExpression:\n')
        if inpt.lower() == 'exit':
            break
        answer = tokenize(inpt)
        if answer != None:
            answer = shunting(answer)
            if answer != None:
                answer = eval_rp(answer)
                if answer != None:
                    print(f'\033[1;32;1m{answer}')
                    write_answer = ''
                    if type(answer) == int or type(answer) == float:
                        write_answer = str(answer)
                    else:
                        for k, i in enumerate(answer):
                            write_answer += str(i)
                            if k != len(answer) - 1:
                                write_answer += ' '
                    with open('./../answers.txt', 'a') as answers:
                        answers.write(write_answer + '\n')
