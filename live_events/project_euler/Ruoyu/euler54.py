#Vars
Wins = 0
H1 = []
H2 = []
Ranks = {   '2': 2,
            '3': 3,
            '4': 4,
            '5': 5,
            '6': 6,
            '7': 7,
            '8': 8,
            '9': 9,
            'T': 10,
            'J': 11,
            'Q': 12,
            'K': 13,
            'A': 14 }

#User def functions
##Check for straight
def IsStraight(Hand):
    Hand.sort()
    Hand.reverse()
    HighCard = Hand[0]
    for i, e in enumerate(Hand):
        if e != HighCard - i:
            return False
    return True

def RateHand(Hand):
    HandRanks = []
    HandSuits = set()
    RankAmounts = [0 for i in range(2, 15)]
    HandRating = 0
    IsFlush = False
    for i in Hand:
        HandRanks.append(Ranks[i[0]])
        RankAmounts[Ranks[i[0]] - 2] += 1
        HandSuits.add(i[1])
    if len(HandSuits) == 1:
        IsFlush = True
    IsStraightHand = IsStraight(HandRanks)
    HandRanks.sort()
    HandRanks.reverse()
    if IsStraightHand and IsFlush:
        return [8, HandRanks[0]]
    elif IsFlush:
        return [5] + HandRanks
    elif IsStraightHand:
        return [4, HandRanks[0]]
    elif 4 in RankAmounts:
        return [7, RankAmounts.index(4) + 2]
    elif 3 in RankAmounts:
        if 2 in RankAmounts:
            return [6, RankAmounts.index(3) + 2]
        return [3, RankAmounts.index(3) + 2]
    elif 2 in RankAmounts:
        if RankAmounts.count(2) == 2:
            HandRanks = []
            for i in range(2):
                _ = RankAmounts.index(2)
                HandRanks.append(_ + 2)
                RankAmounts[_] = 0
            HandRanks.reverse()
            return [2] + HandRanks + [RankAmounts.index(1) + 2]
        HandRanks.pop(HandRanks.index(RankAmounts.index(2) + 2))
        return [1] + [HandRanks.pop(HandRanks.index(RankAmounts.index(2) + 2))] + HandRanks
    else:
        return [0] + HandRanks 

#Rate poker hands
if __name__ == '__main__':
    with open('p054_poker.txt', 'r') as p:
        for Hand in p:
            Hand = Hand.split(' ')
            H1 = Hand[:5]
            H2 = Hand[5:]
            if RateHand(H1) > RateHand(H2):
                Wins += 1
    print(Wins)
