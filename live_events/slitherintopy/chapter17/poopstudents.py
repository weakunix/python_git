'''
Write a class that models a students grades for particular modules. The class will have four methods. The first should initialise the student. The student should have a name and age. The grades should be modelled as a dictionary in which the key is the name of the module and the value is the grade. This should initially be empty. The second method is called add_module() and should add a module to the student object. The third is called update_module_grade() and should update the grade for a particular module. The final method is called show_grades() and should print out the students modules and the grade associated with each module.
'''

class student:
    def init(self, name, age):
        self.name = name
        self.age = age
        self.courses = {}
    def add_module(self, course = "UNDEF", grade = 0):
        self.courses[str(course)] = int(grade)
    def update_grade(self, course, grade):
        self.courses[str(course)] = int(grade)
    def show_grades(self):
        print(f"{self.name}'s grades are:")
        print(self.courses)

s = student()
s.init("Ruoyu", 12)
s.add_module("Dancing")
s.add_module("DZNR", 89)
s.update_grade("Dancing", 100) #ruoyu nice job! u did great! XD
s.show_grades() #I wonder why you're such a good dancer! You've been practicing with Sophia!
