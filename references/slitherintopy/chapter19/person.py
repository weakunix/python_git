'''
Write a Python program that contains a class called Person. An instance of a Person should have name and age attributes. You should be able to print an instance of the class which, for example, should output John is 28 years old.

Your class should have a method called fromBirthYear() which as parameters should take an age and a birth year. For example, fromBirthYear('John', 1990) should return an instance of Person whose age is 29 (at the time of writing this book, 2019).
'''

class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def __str__(self):
        return str(self.name) + " is " + str(self.age) + " years old"
    @classmethod
    def fromBirthYear(cls, name, year):
        return cls(name, 2020 - year)

qingqing = Person("QingQing", 3)
ruoyu = Person("Royandle", 12)
jason = Person("Jasone", 14)
duoduo = Person.fromBirthYear("Duoduodadle", 2005)

print(qingqing)
print(ruoyu)
print(jason)
print(duoduo)

#works