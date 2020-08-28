class Characters:
    def __init__(self):
        self.isAlive = True
        # self.

    def dayrole(self):
        pass

    def nightrole(self):
        pass


class Killer(Characters):
    def __init__(self):
        super().__init__()

    def Foil(self):
        pass

    def Buy(self):
        pass

    def kill(self, target):
        pass

    def blackMail(self, target):
        pass


class Detective(Characters):
    def __init__(self):
        super().__init__()

    def See(self):
        pass

    def day(self):
        pass

    def workScientist(self):
        # return person
        pass


class Hacker(Characters):
    def __init__(self):
        super().__init__()

    def Fake(self):
        pass

    def See(self):
        pass

    def BlockMail(self):
        pass


class Scientist(Characters):
    def __init__(self):
        super().__init__()

    def Dna(self):
        pass

    def Upgrade(self):
        pass

    def Trap(self):
        pass


class Witch(Characters):
    def __init__(self):
        super().__init__()

    def See(self):
        pass

    def Buy(self):
        pass

    def BlockAss(self):
        pass


class Hunter(Characters):
    def __init__(self):
        super().__init__()

    def Avenge(self):
        pass

    def Buy(self):
        pass

    def FindWeapon(self):
        pass


class Workhorse(Characters):
    def __init__(self):
        super().__init__()
        self.distractsLeft = 5
        self.exposeRole = False

    def getKnife(self):
        pass

    def workHorse(self):
        pass

    def lecture(self):
        self.distractsLeft -= 1
        self.exposeRole = True


class Overprotective(Characters):
    def __init__(self):
        super().__init__()
        self.deflect = 3
        self.cooldownOP = 3

    def deflectBullet(self, isKnife):
        if not isKnife:
            if self.deflect > 0:
                self.deflect -= 1
                return True
            return
        return

    def buy(self):
        pass

    def OPSleep(self, target, client):
        if self.cooldownOP <= 0:
            a = client.get_user(int(target))
            a.send('You have been overprotected for the night')
            return True
        return


class Millionaire(Characters):
    def __init__(self):
        super().__init__()
        pass  # self.

    def Bribe(self):
        pass

    def Influence(self):
        pass

    def Business(self):
        pass
