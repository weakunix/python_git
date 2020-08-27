# testing how classes work

class cattle:
    def __init__(self, name):  # shared variables along both cows and bulls
        self.age = 0
        self.name = name


class cow(cattle):
    def __init__(self):
        self.__secret = True  # the cow has secrets and it is a private variable meaning it can't be accessed outside 0_o
        super().__init__('BingBingBing')  #initiate parent class with BINGBINGBING as name and inherits age and name

    def milkCow(self):
        print("cow has been milked")  # exclusive to cow class cow can get milked, bulls can not


class bull(cattle):
    def __init__(self):
        self.secret = False  # the bull has NOTHING to hide
        super().__init__('Mootbing')  # initiate parent class with MOOTBING as name and inherits age and name

    def bullShit(self):
        print('STOP BULLSHITTING')  # RAAAAA


instancebull = bull()  # makes an instance of the bull class which inherits cattle
instancecow = cow()  # makes an instance of the cow class which inherits cattle
print(instancebull.secret)  # public
try:
    print(instancecow.__secret)  # it will error bc it is priv variable (shown by __)
except:
    print("can't print private variable!!!!")
'''for i in range(3):
    print(instancebull.name + "\n")
    print(instancecow.name + "\n")
    instancebull.bullShit()
    instancecow.milkCow()
    print(str(instancebull.age))
    print(str(instancecow.age))'''
