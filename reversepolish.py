#vars
alln=["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]
allo={  "+": lambda n1,n2: n1+n2,
        "-": lambda n1,n2: n1-n2,
        "*": lambda n1,n2: n1*n2,
        "/": lambda n1,n2: n1/n2,
        "^": lambda n1,n2: n1**n2 }
pr={    "+": 0,
        "-": 0,
        "*": 1,
        "/": 1,
        "^": 2 }

#main
def convert_number(tok):
    try:
        x=float(tok)
    except:
        x=None
    return x

def eval_rp(expr):
    """
    input: a string or a list of token strings (either numbers or operators)
    output: evaluate reverse polish
    """
    if isinstance(expr, str):
        expr=tokenize(expr)
    num=[]
    for i in expr:
        x=convert_number(i)
        if x is not None:
            num.append(x)
        else:
            if i in allo:
                if len(num)>0:
                    n2=num.pop()
                else:
                    raise SystemExit("Error: invalid expression")
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
    for i in expr:
        if i in alln:
            n+=i
        elif i==".":
            if dot==0:
                n+=i
                dot=1
            else:
                raise SystemExit("Error: bad format {}.".format(n))
        elif i==" ":
            if n!="":
                rpe.append(n)
                n=""
                dot=0
        elif i in allo or i=="(" or i==")":
            if n!="":
                rpe.append(n)
                n=""
                dot=0
            rpe.append(i)
        else:
            raise SystemExit("Error: unrecognized token \"{}\"".format(i))
    if n!="":
        rpe.append(n)
    return rpe

def shunting(expr):
    """
    input: a list of infix tokens
    output: a list of reverse polish tokens
    """
    o=[]
    n=[]
    for i in expr:
        if convert_number(i) is not None:
            n.append(i)
        elif i in allo:
            while len(o)>0:
                if o[-1]!="(" and pr[o[-1]]>=pr[i]:
                    n.append(o.pop())
                else:
                    break
            o.append(i)
        elif i=="(":
            o.append(i)
        elif i==")":
            while len(o)>0 and o[-1]!="(":
                n.append(o.pop())
            if len(o)>0 and o[-1]=="(":
                o.pop()
            else:
                raise SystemExit("Error: bad format {}, no matching left parenthesis.".format(expr))
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
