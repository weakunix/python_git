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