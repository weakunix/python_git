'''
Create a Line class. The line class should have four attributes: an x1 and a y1 coordinate for one point on the line and an x2 and a y2 coordinate for the second point on the line. You should be able to do a few things with an instance of a line. You should be able to call the len method on a line to show its length, add two lines together, subtract two lines, multiply a line by an integer, print the line and compare two lines to see if they are equal. In this case equality means both lines are the same length. When implemented correctly, you should be able to use the Line class as follows:
'''

class Line:
    def __init__(self, x1, y1, x2, y2):
        self.x1 = x1
        self.x2 = x2
        self.y1 = x1
        self.y2 = x2
    
    def __len__(self):
        return (self.y2 - self.y1)//(self.x2 - self.x1)
    
    def __add__(self, other):
        return len(self) + len(other)
    
    def __sub__(self, other):
        return len(self) - len(other)
    
    def __mul__(self, other):
        return len(self) * len(other)
    
    def __truediv__(self, other):
        return len(self) / len(other)
    
    def __eq__(self, other):
        return len(self) == len(other)

    def __str__(self):
        return "Line details:\nPoint 1: ({}, {})\nPoint 1: ({}, {})".format(self.x1, self.y1, self.x2, self.y2)

a = Line(10,10, 0, 0)
b = Line(0, 0, 10, 10)

print(a)
print(b)

print(len(a))
print(len(b))
print(a + b)
print(a - b)
print(a * b)
print(a / b)
print(a == b)