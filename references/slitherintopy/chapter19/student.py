'''
Write a Student class that has initializes a student with 3 attributes: name, grades and student_number. Grades should be a dictionary of modules to grades. The student number of the first student instance should be 19343553. The student number of the second student instance should be 19343554 and so on. You should have three methods, add_module() which takes one parameter, a module name, and initialises the grade to 0. The second method should be, update_module() which takes two parameters, the module name and the grade for the module. The final method should allow the user to print a student.

Think carefully about how you will implement the increasing student number.
'''

class Student:
    studentId = 19343553
    def __init__(self, name):
        self.name = name
        self.grades = {}
        self.id = Student.studentId
        Student.studentId += 1
    
    def add_module(self, moduleName):
        self.grades[str(moduleName)] = 0

    def update_module(self, moduleName, grade):
        self.grades[str(moduleName)] = int(grade)
    
    def __str__(self):
        return "Name: " + self.name + "\nStudent Number: " + str(self.id) + "\nGrades: \n" + str(self.grades).replace("{", "").replace("}", "").replace("'", "").replace(",", "\n")

    @staticmethod
    def validate(score):
        return 0 <= score <= 100


royandle = Student("Ruoyu")
jasone = Student("Jason")

royandle.add_module("Python")
jasone.add_module("Java")
royandle.add_module("Dancing")

royandle.update_module("Python", 100)
jasone.update_module("Java", 90)
royandle.update_module("Dancing", -10000)

print(royandle)
print(jasone)

print(royandle.validate(1000)) #false
print(jasone.validate(10)) #true, but you get da broomsticcc