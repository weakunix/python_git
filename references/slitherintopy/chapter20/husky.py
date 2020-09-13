#program I wrote to get familiar with multiple inheritance

class dog:
    count = 0
    def __init__(self, age = 0, color = "black"):
        self.age = age
        self.color = color
        dog.count += 1
    
    def showcolor(self):
        print(self.color)
    
    @staticmethod
    def bark():
        print("woof")

class husky(dog):
    def __init__(self, age = 6, color = "grey and white"):
        super().__init__(age, color)
    
    @staticmethod
    def furcoat():
        print("so cosy!")

class germanShepard(dog):
    def __init__(self, age = 5, color = "brown"):
        super().__init__(age, color)
    
    @staticmethod
    def loudBark():
        print("WOOOOF!!!!!!")

class doggiekid(husky, germanShepard):
    def __init__(self, age, color):
        husky.__init__(self, age, color)
        germanShepard.__init__(self, age, color)
    
    @staticmethod
    def adorable():
        print("I'm cute! 0w0")

kiddo = doggiekid(0, "brownish grey")

kiddo.bark()

kiddo.loudBark()

kiddo.furcoat()

kiddo.showcolor()

kiddo.adorable()
