from bs4 import BeautifulSoup
import requests
import re

def calcSchedule():
	site = BeautifulSoup(requests.get("https://calendar.google.com/calendar/u/0/htmlembed?src=vt09lfemhmgtajic4dvmou1u5jcaueef@import.calendar.google.com&amp;ctz=America/New_York").content, 'html.parser') 
	for classes in site.find_all("span", class_="event-summary"):
		if classes is not None:
			print(classes.find_parents())
			if classes.find_parents('td', class_="null cell-today") != [] or classes.find_parents('td', class_="cell-last-row cell-today") != []:
				print(classes)
				classes = str(re.sub("<.*>", "",  classes))
				print(classes)

calcSchedule()