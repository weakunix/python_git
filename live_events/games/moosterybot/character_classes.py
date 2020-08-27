class Workhorse:
    def __init__(self):
        self.distractsLeft = 5
        self.exposeRole = False

    def lecture(self):
        self.distractsLeft -= 1
        self.exposeRole = True


class Overprotective:
    def __init__(self):
        self.deflect = 3
        self.cooldownOP = 3

    def deflectBullet(self, isKnife):
        if not isKnife:
            if self.deflect > 0:
                self.deflect -= 1
                return True
            return
        return

    def OPSleep(self, target, client):
        if self.cooldownOP <= 0:
            a = client.get_user(int(target))
            a.send('You have been frozen for the night')
            return True
        return
