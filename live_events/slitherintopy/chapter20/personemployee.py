'''
Create two classes: Person and Employee. The person class should have name and age attributes. The employee class should have one additional employeeId attribute. The employ should also have clock_in and clock_out methods. When implemented correctly, you should be able to use the two classes as follows:
'''

class Person:
    def __init__(self, name, age):
        self.age = age
        self.name = name

class Employee(Person):
    employeeID = 1
    def __init__(self, name, age):
        super().__init__(name, age)
        self.employeeID = Employee.employeeID
        Employee.employeeID += 1
    
    def clock_in(self):
        print("Long day ahead! Get working!")
    
    def clock_out(self):
        print("Nice work!")

Ruoyu = Employee("Ruoyu", 12) #sorry FBI for child labor
Ruoyu.clock_in()
Ruoyu.clock_out()
print(Ruoyu.employeeID)
Jason = Employee("Jason", 14) #sorry FBI for child labor
Jason.clock_in()
Jason.clock_out()
print(Jason.employeeID)