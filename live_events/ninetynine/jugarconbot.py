#imports
import random

#vars
cardl = [] #cards left
cardp = [] #cards played
cardn = 0 #amount of cards per player

#filling cardl
for i in range(1, 14):
	for k in range(4):
		cardl.append(i)
for i in range(2):
	cardl.append(14)
	
#ask for amount of cards per player
while True:
	cardn = input('How many cards per player?\n')
	try: #see if input was integer
		cardn = int(cardn)
		break
	except:
		print('Input was not an integer\n')

