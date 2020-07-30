#imports


# user defined functions
def gcd(*n):
    if len(n) == 0:
        raise SystemExit("Error: at least one argument for gcd.")
    if len(n) == 1:
        return n
    if len(n) == 2:
        return gcd_2n(*n)
    if len(n) > 2:
        a = n[0]
        for i in n:
            a = gcd_2n(a, i)
        return a


def gcd_2n(a, b):
    while a != 0 and b != 0:
        a %= b
        if a == 0:
            return b
        b %= a
        if b == 0:
            return a
def lcm(*n):
    if len(n) == 0:
        raise SystemExit("Error: at least one argument for lcm.")
    if len(n) == 1:
        return n
    if len(n) == 2:
        return lcm_2n(*n)
    if len(n) > 2:
        a = n[0]
        for i in n:
            a = lcm_2n(a, i)
        return a
def lcm_2n(a, b):
    g = gcd_2n(a, b)
    a = a * b / g
    return a

#vars
alln = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]
allo = {  "+": lambda n1,n2: n1+n2,
          "-": lambda n1,n2: n1-n2,
          "*": lambda n1,n2: n1*n2,
          "/": lambda n1,n2: n1/n2,
          "^": lambda n1,n2: n1**n2,
          'uniadd' : lambda x: x,
          'unisub' : lambda x: -x }
unio = { 'uniadd', 'unisub' }
allf = { 'max' : max,
         'min' : min,
         'gcd' : gcd,
         'lcm' : lcm }
pr = {    "+": 0,
          "-": 0,
          "*": 1,
          "/": 1,
          "^": 2,
          'uniadd' : 3,
          'unisub' : 3 }

#main
def convert_number(tok):
    try:
        x = float(tok)
    except:
        x = None
    return x

def eval_rp(expr):
    """
    input: a string or a list of token strings (either numbers or operators) or functions (list of 2 element [function_name, number_of_arguments])
    output: evaluate reverse polish
    """
    if isinstance(expr, str):
        expr = tokenize(expr)
    num = []
    for i in expr:
        if isinstance(i, list): # function
            func = i[0]
            if func not in allf:
                raise SystemExit("Error: unknown function {}".format(func))
            narg = i[1]
            arg = []
            while narg > 0:
                arg.append(num.pop())
                narg -= 1
            arg.reverse()
            num.append(allf[func](*arg))
        else:
            x=convert_number(i)
            if x is not None:
                num.append(x)
            else:
                if i in allo:
                    if len(num)>0:
                        n2=num.pop()
                    else:
                        raise SystemExit("Error: invalid expression")
                    if i in unio:
                        num.append(allo[i](n2))
                    else:
                        if len(num)>0:
                            n1=num.pop()
                        else:
                            raise SystemExit("Error: invalid expression")
                        num.append(allo[i](n1,n2))
                else:
                    raise SystemExit("Error: unrecognized token \"{}\"".format(i))
    if len(num)!=1:
        raise SystemExit("Error: invalid expression")
    return num[0]


def tokenize(expr):
    """
    input: a string of reverse polish expression
    output: a list of tokens from the string
    """
    rpe=[]
    n=""
    dot=0
    count=0
    var = ''
    isvar = False
    for i in expr:
        if isvar:
            if i == " " or i == "(" or i == ")" or i in allo:
                rpe.append(var)
                if i != " ":
                    rpe.append(i)
                isvar = False
            else:
                var += i
        else:
            if i in alln:
                n+=i
            elif i==".":
                if dot==0:
                    n+=i
                    dot=1
                else:
                    raise SystemExit("Error: bad format {}.".format(n))
            elif i==" " or i==",":
                if n!="":
                    rpe.append(n)
                    n=""
                    dot=0
                if i != " ":
                    rpe.append(i)
            elif i in allo or i=="(" or i==")":
                if n!="":
                    rpe.append(n)
                    n=""
                    dot=0
                rpe.append(i)
            else:
                isvar = True
                var = i
            #else:
            #    raise SystemExit("Error: unrecognized token \"{}\"".format(i))
    if n!="":
        rpe.append(n)
    return rpe

def shunting(expr):
    """
    input: a list of infix tokens
    output: a list of reverse polish tokens
    """
    o = [] # operator stack
    n = [] # output stack
    c = [] # func arg counter stack
    arginc = False
    check_uni = True
    for i in expr:
        if i in allf:
            if arginc and len(o) > 0 and o[-1] in allf:
                c[-1] += 1
                arginc = False
            o.append(i)
            c.append(0)
            arginc = True
            check_uni = False
        else:
            if convert_number(i) is not None:
                if arginc and len(o) > 0 and o[-1] in allf:
                    c[-1] += 1
                    arginc = False
                n.append(i)
                check_uni = False
            elif i in allo:
                if arginc and len(o) > 0 and o[-1] in allf:
                    c[-1] += 1
                    arginc = False
                # handle leading +/- case
                if check_uni:
                    if i == '+':
                        o.append('uniadd')
                    elif i == '-':
                        o.append('unisub')
                    else:
                        raise SystemExit("Error: bad format, unitary operator can only be + or -.")
                else:
                    while len(o)>0:
                        if o[-1]!="(" and o[-1] not in allf and pr[o[-1]]>=pr[i]:
                            n.append(o.pop())
                        else:
                            break
                    o.append(i)
                check_uni = True
            elif i=="(":
                if len(o) > 0 and o[-1] not in allf:
                    o.append(i)
                check_uni = True
            elif i==",":
                while len(o)>0 and o[-1] not in allf:
                    n.append(o.pop())
                if len(o) == 0 or o[-1] not in allf:
                    raise SystemExit("Error: bad format {}, comma outside a function.".format(expr))
                arginc = True
                check_uni = True
            elif i==")":
                while len(o)>0 and o[-1]!="(" and o[-1] not in allf:
                    n.append(o.pop())
                if len(o) == 0:
                    raise SystemExit("Error: bad format {}, no matching left parenthesis.".format(expr))
                elif o[-1] in allf:
                    n.append([o.pop(), c.pop()])
                elif o[-1]=="(":
                    o.pop()
                else:
                    raise SystemExit("Impossible!")
                check_uni = False
            else:
                raise SystemExit("Error: unrecognized token \"{}\"".format(i))
    while len(o)>0:
        if o[-1]!="(":
            n.append(o.pop())
        else:
            raise SystemExit("Error: bad format {}, no matching right parenthesis.".format(expr))
    return n

def eval_infix(expr):
    if isinstance(expr, str):
        expr=tokenize(expr)
    expr=shunting(expr)
    return eval_rp(expr)


if __name__=="__main__":
    n=input("Input:\n")
    print(eval_infix(n))
