import requests
from bs4 import BeautifulSoup
import re

'''
parafoRegExed = re.sub('</div>]', "", str(re.sub('\[<div class="fc-day-number">', "", str(BeautifulSoup(requests.get("https://rutgersprep.myschoolapp.com/app/student#studentmyday/schedule").content, 'html.parser')))))

schedules = []
'''

todo = {
	"English": ["analysis da text", "tonite"], #naibing class: have to do cows, due mootbing
	"Math": ["do yah algeeebruh", "next wek"]
}

'''

print("Your today schedule:\n " + str(schedules).replace("[", "").replace("]", ""))

print("TODO: \n" + str(todos).replace("[", "").replace("]", "")

#sounds like fed-ex IK lol

print(parafoRegExed)
'''

for className in todo:
	print("\nYou have assignment in \nClass: " + str(className) + "\nDesc: " + str(todo[str(className)][0]) + "\nDue on: " + str(todo[str(className)][1]))

