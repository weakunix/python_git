'''
Create a Shape class. The shape class should have two attributes: num_sides and side_length. It should also have one method called show_type()

Create two other classes: Triangle and Pentagon. Each of these classes should inherit from the Shape class.

Both the Triangle and Pentagon classes should have area() methods.

When implemented correctly, you should be able to use your classes as follows:
'''

class Shape:
    def __init__(self, num_sides, side_length):
        self.sides = num_sides
        self.len = side_length
    
    @staticmethod
    def show_type():
        print("It\'s a shape")

class Triangle(Shape):
    def __init__(self, sidelen):
        super().__init__(3, sidelen)

    @staticmethod
    def show_type():
        print("Triangle")
    
    def area(self):
        pass
        #print(str((self.len * self.len) / 2)) formula and shit here

class Pentagon(Shape):
    def __init__(self, sidelen):
        super().__init__(5, sidelen)
    
    @staticmethod
    def show_type():
        print("Pentagon")
    
    def area(self):
        pass
        #print(str(self.len * self.sides)) formula and shit here

#

pent = Pentagon(4)
pent.show_type()
pent.area()

tri = Triangle(3)
tri.show_type()
tri.area()

shap = Shape(10, 10)
shap.show_type()