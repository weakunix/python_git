'''
Write a class that models a Cirlce. The circle class will have four methods. The first will initialise the circle. The initialise() method should take three parameters, x_coord, y_coord, and radius. This will set the circles x and y coordinates and it radius. The next method is called calc_area(). It should calculate the area of the circle (Look up the formula). The third method is called calc_perimeter() and should calculate the circumference of the circle (Look up the formula). The fourth method is overlaps(). It should take as an argument, another circle and print out whether or not the two circles overlap.
'''


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
