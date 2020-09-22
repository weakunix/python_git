import requests
from bs4 import BeautifulSoup
import re
import os
																																		#v here add html instead of just embed to get html version of the calendar
todoScraped = BeautifulSoup(requests.get("https://calendar.google.com/calendar/u/0/htmlembed?src=a7agc1d6cg82r3on8m6q9ifoqo7bf2l2@import.calendar.google.com&amp;ctz=America/New_York").content, 'html.parser') 
scheduleScraped = BeautifulSoup(requests.get("https://calendar.google.com/calendar/u/0/htmlembed?src=vt09lfemhmgtajic4dvmou1u5jcaueef@import.calendar.google.com&amp;ctz=America/New_York").content, 'html.parser') 

def clear():
	if os.name == 'nt': 
		os.system('cls') #windows
	elif os.name == 'darwin':
		os.system('clear') 
	elif os.name == 'posix':
		try:
			import console; console.clear() #pythonista
		except:
			pass
		else:
			return
		try:
			os.system('clear') #mac/linux
		except:
			pass
	else: 
	    os.system('clear') #mac/linux

def calcTodo():
	clear()
	sub = []
	desc = []
	for event in todoScraped.find_all("span", class_="event-summary"):
		if event != None:
			event = str(event).replace('<span class="event-summary">', "").replace("</span>", "").replace("&amp;", "&")
			chars = []
			i = 0
			while "-" not in chars:
				chars.append(event[i])
				i += 1
			sub.append("".join(chars).replace("-", ""))
			desc.append(event.replace("".join(chars), ""))
	return sub, desc

def calcSchedule():
	clear()
	sch = []
	tim = ["Day"]
	for classes in scheduleScraped.find_all("span", class_="event-summary"):
		if classes is not None:
			if classes.find_parents('td', class_="null cell-today") != [] or classes.find_parents('td', class_="cell-last-row cell-today") != []:
				classes = str(classes).replace('<span class="event-summary">', "").replace("</span>", "").replace("&amp;", "&")
				sch.append(str(classes))
	
	for time in scheduleScraped.find_all("span", class_="event-time"): #have to MANUALLY reverse 4 hours bc it always on dumbass UTC
		if time != None:
			time = str(time).replace('<span class="event-time">', "").replace("</span>", "").replace("&amp;", "&")
			time = time.split(":") if time != "3pm" else [3, "00pm"]
			time[0] = str(int(time[0]) - 4)
			if int(time[0]) < 0:
				time[0] = str(12 + int(time[0]))
			time = ":".join(time)
			if time not in tim:
				tim.append(time)

	return sch, tim

def makedict(assignment, todo, classNames):
	for i in range(len(assignment)):
		todo[classNames[i]] = [assignment[i], "a"] #make new value in dict with about and due date
	return todo
#print("Your today schedule:\n " + str(schedules).replace("[", "").replace("]", ""))
#sounds like fed-ex IK lol

def display(todo):
	for className in todo:
		print("\nYou have assignment in \nClass: " + str(className) + "\nDesc: " + str(todo[str(className)][0]) + "\nDue on: " + str(todo[str(className)][1]))

def displays(schedules, stime):
	for i in range(len(stime)):
		print(f"\nClass at {str(stime[i])}:\n {str(schedules[i])}")

def main():
	assignment = []
	classNames = []
	todo = {}
	schedules = []
	stime = []
	while True:
		clear()
		sORt = input("\nschedule/todo/exit\n\n>>>")
		if sORt.lower() == "schedule":
			schedules, stime = calcSchedule()
			displays(schedules, stime)
			input("\nEnter to continue...")
		elif sORt.lower() == "todo":
			appends = calcTodo()
			classNames = appends[0]
			assignment = appends[1]
			todo = makedict(assignment, todo, classNames)
			display(todo)
			input("\nEnter to continue...") 
		elif sORt.lower() == "exit":
			raise SystemExit("Done")
		else:
			print("Invalid Command!")

if __name__ == "__main__":
	main()