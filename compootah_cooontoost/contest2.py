import re

def rearrangedString(s, ListOfSorted = [], NumbersToCharacterNoRepeat = {}, Final = {}, FinalFinalFinal = []):
    s = re.sub("\W*", "", s)
    for letter in s:
        ListOfSorted.append(letter)
    ListOfSorted = sorted(ListOfSorted)

    for char in ListOfSorted:
        if ListOfSorted.count(char) in NumbersToCharacterNoRepeat.keys():
            if char not in NumbersToCharacterNoRepeat[ListOfSorted.count(char)]:
                NumbersToCharacterNoRepeat[ListOfSorted.count(char)].append(char)
        else:
            NumbersToCharacterNoRepeat[ListOfSorted.count(char)] = [char]
    
    for i in list(reversed(sorted(NumbersToCharacterNoRepeat.keys()))):
        Final[i] = NumbersToCharacterNoRepeat[i]

    for i in range(len(Final)):
        MagicValue = list(Final.keys())[i]
        if i % 2 == 0:
            Final[MagicValue] = sorted(Final[MagicValue])
        else:
            Final[MagicValue] = list(reversed(sorted(Final[MagicValue])))

    for key in Final.keys():
        FinalFinalFinal.append(str(key) + "".join(Final[key]))

    return ",".join(FinalFinalFinal)

    
print(rearrangedString("This is an Example of Sorting an interesting string"))

'''
ArrayNoRepeats = {}, flipped = {}, FlipCounter = 0, FinalArray = []
for char in re.sub("\W*", "", s):
        temp = 0
        if char in ArrayNoRepeats.keys():
            temp = ArrayNoRepeats[char]
            del ArrayNoRepeats[char]
        ArrayNoRepeats[char] = temp + 1
        print(ArrayNoRepeats)

    for char in ArrayNoRepeats:
        if int(ArrayNoRepeats[char]) in flipped.keys():
            flipped[ArrayNoRepeats[char]].append(char)
        else:
            flipped[ArrayNoRepeats[char]] = [char]

    for key in flipped.keys():
        FinalArray.append(str(key) + "".join(flipped[key]))

    return ",".join(FinalArray)


    blocks of 6 - acending
    of 5 -decending
    4 - acending
    3 - decending
'''

    #return completed


#print()