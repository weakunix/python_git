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
