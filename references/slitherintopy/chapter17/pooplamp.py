'''
Write a class that models a Lamp. The lamp class will have have two methods. The first will initialise the lamp and is called plug_in(). This will set the is_on attribute which is a boolean to False. The second method is called toggle(). If the lamp is off, it will turn it on (set is_on to True) and if the lamp is on, it will turn it off (set is_on to True).
'''

class Lamp:
    def plug_in(self):
        self.isOn = False
    def is_on(self):
        return self.isOn
    def toggle(self):
        if self.isOn:
            self.isOn = False
        else:
            self.isOn = True

lamp = Lamp()
lamp.plug_in()
print(lamp.is_on())
lamp.toggle()
print(lamp.is_on())
lamp.is_on()