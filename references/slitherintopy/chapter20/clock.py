'''
Create a Clock class. It should have three attributes: hour, minute, and second. It should also have a method called show_time() that displays the time in 24 hour time. It should also have a method called tick() that advances the time by 1 second.

Create a Calendar class. It should have three attributes: day, month, and year. It should have two methods, one called show_date() and the other called next() that advances the date to the next day.

Create a third class called CalendarClock that inherits from both Clock and Calendar. It should have one method called tick() that advances the time by 1 second, and a second method, show_date_time() that shows the date and time.
'''

class Clock:
    def __init__(self, hour, minute, second):
        self.hour = hour
        self.minute = minute
        self.second = second
    
    def show_time(self):
        print("The time is {}:{}:{}".format(self.hour, self.minute, self.second))
    
    def tick(self):
        if self.second < 60:
            self.second += 1
        if self.minute < 60 and self.second >= 60:
            self.minute += 1
            self.second = 0
        if self.hour < 24 and self.minute >= 60:
            self.hour += 1
            self.minute = 0 
        if self.hour >= 24:
            self.hour = 0

class Calendar:
    def __init__(self, day, month, year):
        self.day = day
        self.month = month
        self.year = year
    
    def show_date(self):
        print("The date is {}/{}/{}".format(self.day, self.month, self.year)) 
    
    def nextt(self):
        if self.day < 31:
            self.day += 1
            self.hour = 0
        if self.month <= 12 and self.day >= 30:
            self.month += 1
            self.day = 1
        if self.month >= 12:
            self.year += 1
            self.month = 1

class CalendarClock(Clock, Calendar):
    def __init__(self, hour, minute, second, day, month, year):
        Clock.__init__(self, hour, minute, second)
        Calendar.__init__(self, day, month, year)
    
    def tick(self):
        if self.second < 60:
            self.second += 1
        if self.minute < 60 and self.second >= 60:
            self.minute += 1
            self.second = 0
        if self.hour < 24 and self.minute >= 60:
            self.hour += 1
            self.minute = 0
        if self.day <= 31 and self.hour >= 24:
            self.day += 1
            self.hour = 0
        if self.month <= 12 and self.day >= 31:
            self.month += 1
            self.day = 1
        if self.month >= 12:
            self.year += 1
            self.month = 1
    
    def show_date_time(self):
        print("The date is {}/{}/{} at {}:{}:{}".format(self.day, self.month, self.year, self.hour, self.minute, self.second))  

clock = Clock(23, 59, 59)
clock.show_time()
clock.tick()
clock.show_time()

calendar = Calendar(30, 12, 2019)
calendar.show_date()
calendar.nextt()
calendar.show_date()

calendarClock = CalendarClock(23, 59, 59, 30, 12, 2019)
calendarClock.show_date_time()
calendarClock.tick()
calendarClock.show_date_time()
