import requests
from bs4 import BeautifulSoup
import re

sup = BeautifulSoup(requests.get("https://calendar.google.com/calendar/u/0/htmlembed?src=a7agc1d6cg82r3on8m6q9ifoqo7bf2l2@import.calendar.google.com&amp;ctz=America/New_York").content, 'html.parser') 

assignment = []
classNames = []
todo = {}
schedules = []

for event in sup.find_all("span", class_="event-summary"):
	if event != None:
		event = str(event).replace('<span class="event-summary">', "").replace("</span>", "").replace("&amp;", "&")
		chars = []
		i = 0
		while "-" not in chars:
			chars.append(event[i])
			i += 1
		classNames.append("".join(chars).replace("-", ""))
		assignment.append(event.replace("".join(chars), ""))

for i in range(len(assignment)):
	todo[classNames[i]] = [assignment[i], "a"]
#print("Your today schedule:\n " + str(schedules).replace("[", "").replace("]", ""))
#sounds like fed-ex IK lol
for className in todo:
	print("\nYou have assignment in \nClass: " + str(className) + "\nDesc: " + str(todo[str(className)][0]) + "\nDue on: " + str(todo[str(className)][1]))

