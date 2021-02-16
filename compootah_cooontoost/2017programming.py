'''""
{[(2+3)*6/10}
bracket can go in 8, 10, 13
'''

StringToProcess = input("String>>>\n").replace(" ", "")
IsClosed = [
    True, # ()
    True, # []
    True # {}
]

for character in StringToProcess:
    if character == "(" or  character == ")":
        IsClosed[0] = not IsClosed[0]
    elif character == "[" or  character == "]":
        IsClosed[1] = not IsClosed[1]
    elif character == "{" or  character == "}":
        IsClosed[2] = not IsClosed[2]

print(IsClosed)

def Remove(symbol):
    Temp = False
    TempString = []
    index = [0,0]
    if symbol == "()":
        for i in range(len(StringToProcess)):
            if StringToProcess[i] == "(":
                Temp = True
                index[0] = i
            if not Temp:
                TempString.append(StringToProcess[i])
            if Temp and StringToProcess[i] == ")":
                Temp = False
                index[1] = i
    return "".join(TempString), index

print(Remove("()"))

def IsNotNumber(AString):
    if AString == "+" or  AString == "-" or  AString == "*" or  AString == "/":
        return True
    return False

def RemoveSomething(AString, ABrackets):
    BeginIndex = 0
    Indexes = []
    for i in range(len(AString)):
        if IsNotNumber(AString[i]) or i == len(AString) - 1:
            Indexes.append(i + 1)
            print(AString[i])
    return Indexes


if not IsClosed[0]:
    Difference = 0
    Indexies = RemoveSomething(StringToProcess, "()")
elif not IsClosed[1]:
    Removed = Remove("()")
    Difference = Removed[1][1] - Removed[1][0] + 1
    Indexies = RemoveSomething(Removed[0], "[]")
elif not IsClosed[2]:
    pass

for i in Indexies:
    print(i + Difference)