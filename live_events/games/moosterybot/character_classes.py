import json


class Characters:
    def __init__(self, playerid, number):
        self.isAlive = True
        self.number = number
        self.id = playerid
        # self.name = random.randint()
        # self.

    def goTo(self, target):
        pass

    def getPlayers(self, uid, key):
        with open('games.json', 'r') as brr:
            target = json.load(brr)
        for i in range(len(target)):
            if target[key] == str(uid):
                return True
        return False

    def getRoleInList(self, uid, key):
        with open('roles.json', 'r') as brr:
            role = json.load(brr)
        for i in range(len(role)):
            if role[key] == str(uid):
                return True
        return False

    def getRole(self):
        uid = self.id
        with open('roles.json', 'r') as brr:
            role = json.load(brr)
        with open('games.json', 'r') as brr:
            target = json.load(brr)
        for i in range(len(list(target.values()))):
            if str(uid) in list(target.values())[i]:
                place = list(target.values())[i].index(str(uid))
                a = list(role.values())[i][place]
                if int(a) == self.number:
                    nmb = True
                else:
                    nmb = False
                return a, place, nmb
        return False


class Killer(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 0)
        # self.number = 0

    def Passive(self):
        pass

    def Dayrole(self):
        pass

    def Nightrole(self, blackmail, targetid):
        if self.getRole(self.id)[2]:
            if blackmail:
                print('blackmail')
            else:
                print('kill')


class Detective(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 1)
        # self.number = 1

    def Passive(self):
        pass

    def Dayrole(self):
        pass

    def Nightrole(self):
        # return person
        pass


class Hacker(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 2)
        # self.number = 2

    def Passive(self):
        pass

    def Dayrole(self):
        pass

    def Nightrole(self):
        pass


class Scientist(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 6)
        # self.number = 6

    def Passive(self):
        pass

    def Dayrole(self):
        pass

    def Nightrole(self):
        # return person
        pass


class Witch(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 7)
        # self.number = 7

    def Passive(self):
        pass

    def Dayrole(self):
        pass

    def Nightrole(self):
        # return person
        pass


class Hunter(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 3)
        # self.number = 3

    def Passive(self):
        pass

    def Dayrole(self):
        pass

    def Nightrole(self):
        # return person
        pass


class Workhorse(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 8)
        self.distractsLeft = 5
        self.exposeRole = False

    def Passive(self):
        pass

    def Dayrole(self):
        pass

    def Nightrole(self):
        # return person
        pass


class Overprotective(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 5)
        # self.number = 5
        self.deflect = 3
        self.cooldownOP = 3

    def Passive(self):
        pass

    def Dayrole(self):
        pass

    def Nightrole(self):
        # return person
        pass


class Millionaire(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 4)
        # self.number = 4

    def Passive(self):
        pass

    def Dayrole(self):
        pass

    def Nightrole(self):
        # return person
        pass
