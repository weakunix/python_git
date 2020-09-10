import math as albreto

#part 3 idk how do to

class Circle:
    def __init__(self, x, y, radius):
        self.x = x
        self.y = y
        self.radius = radius
    def calc_area(self):
        return (self.radius ** 2) * albreto.pi 
    def calc_perimeter(self):
        return 2 * albreto.pi * self.radius
    def overlap(self, otherObj):
        x = self.x
        y = self.y
        area = self.calc_perimeter
        area2 = otherObj.calc_perimeter
        x2 = otherObj.x
        y2 = otherObj.y
