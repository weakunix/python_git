#imports
import random

#vars
cardl = [] #cards left
sumc = 0 #sum of cards
cardn = 0 #amount of cards per player
bcard = [] #bot cards
pcard = [] #player cards
inpt = '' #input
nums = ['2', '3', '4', '5', '6', '7', '8', '9', '10'] #number cards	

#pre game set ups
##filling cardl
for i in range(1, 14):
	for k in range(4):
		cardl.append(i)
for i in range(2):
	cardl.append(14)
	
##ask if it is first time playing
inpt = input('Is this your first time playing 99?\n')
if inpt != '':
	inpt = inpt[0] #setting input to first letter if input is not enter
if inpt == 'y' or inpt == 'Y': #need tutorial
	inpt = input('Objective of game: Get to 99 but don\'t go over. Make the other person go over 99 to win\n\nHow to play: When you play a card it adds to the sum of all the cards. For example if the first card played was 6 and the second card played was 3, the sum would be 9\n\nCard values:\nA: 1 or 11 (your choice)\n2: 2\n3: 3\n4: 0\n5: 5\n6: 6\n7: 7\n8: 8\n9: 0\n10: -10\nJ: 10\nQ: 10\nK: Automatically to 99\nJoker: Automatically to 99\n\nEnter to continue:\n') #print tutorial

##ask for amount of cards per player
while True:
	cardn = input('How many cards per player? (1 to 10)\n')
	try: #trying to set input to integer
		cardn = int(cardn)
		if cardn <= 10:
			break
		print('Input was greater than 10\n')
	except:
		print('Input was not an integer\n')
		
##giving cards
for i in range(cardn): #player
	pcard.append(cardl.pop(random.randint(0, len(cardl) - 1)))
for i in range(cardn): #bot
	bcard.append(cardl.pop(random.randint(0, len(cardl) - 1)))
	
#user def functions
##player replace card
def p_replace_card(c):
	global pcard
	count = -1
	for i in pcard:
		count += 1
		if i == c:
			pcard.pop(count)
			pcard.append(cardl.pop(random.randint(0, len(cardl) - 1)))
			break

##bot replace card
def b_replace_card(c):
	global bcard
	count = -1
	for i in bcard:
		count += 1
		if i == c:
			bcard.pop(count)
			bcard.append(cardl.pop(random.randint(0, len(cardl) - 1)))
			break
			
##player plays
def player():
	global pcard
	global cardl
	global sumc
	print("Your Cards: ")
	for i in pcard: #print cards
		if i == 1:
			print('[A]', end = '')
		elif i == 11:
			print('[J]', end = '')
		elif i == 12:
			print('[Q]', end = '')
		elif i == 13:
			print('[K]', end = '')
		elif i == 14:
			print('[Joker]', end = '')
		else:
			print('[{}]'.format(i), end = '')
	while True:
		inpt = input('\n\nChoose a card to play:\n')
		if inpt != '':
			if inpt[0] == 'a' or inpt[0] == 'A': #ace
				if 1 in pcard:
					while True:
						inpt = input('Ace is 1 or 11?\n')
						if inpt == '1' or inpt == '11':
							if inpt == '1':
								sumc += 1
							else:
								sumc += 11
							p_replace_card(1)
							break
						else:
							print('\nInput was not 1 or 11\n')
					break
			elif inpt[0] == 'j' or inpt[0] == 'J':
				if len(inpt) > 1:
					if inpt[1] == 'a' or inpt[1] == 'A': #jack
						if 11 in pcard:
							sumc += 10
							p_replace_card(11)
							break
					elif inpt[1] == 'o' or inpt[1] == 'O': #joker
						if 14 in pcard:
							sumc = 99
							p_replace_card(14)
							break
			elif inpt[0] == 'q' or inpt[0] == 'Q': #queen
				if 12 in pcard:
					sumc += 10
					p_replace_card(12)
					break
			elif inpt[0] == 'k' or inpt[0] == 'K': #king
				if 13 in pcard:
					sumc = 99
					p_replace_card(13)
					break
			elif inpt in nums:
				inpt = int(inpt)
				if inpt == 4: #4
					p_replace_card(4)
					break
				elif inpt == 9: #9
					p_replace_card(9)
					break
				elif inpt == 10: #10
					sumc -= 10
					p_replace_card(10)
					break
				else: #other numbers
					sumc += inpt
					p_replace_card(inpt)
					break
	if sumc > 99:
		print('Bot cards:\n')
		for i in bcard: #print cards
			if i == 1:
				print('[A]', end = '')
			elif i == 11:
				print('[J]', end = '')
			elif i == 12:
				print('[Q]', end = '')
			elif i == 13:
				print('[K]', end = '')
			elif i == 14:
				print('[Joker]', end = '')
			else:
				print('[{}]'.format(i), end = '')
		raise SystemExit('\n\nYou lose')
	print('Sum: {}'.format(sumc))

##bot plays
def bot():
	global bcard
	global cardl
	global sumc
	nums = [2, 3, 5, 6, 7, 8]
	power = True #does the bot have all power cards?
	if sumc <= 88:
		for i in bcard:
			if i in nums:
				power = False
				break
		if not power:
			while True:
				power = bcard[random.randint(0, cardn - 1)]
				if power in nums:
					sumc += power
					print('===========\nBot played: {}\nSum: {}\n'.format(power, sumc))
					break
		else:
			power = bcard[random.randint(0, cardn - 1)]
			if power == 1:
				inpt = random.randint(1, 2)
				if inpt == 1:
					sumc += 1
					print('Card played: A(1)\nSum: {}\n'.format(sumc))
				else:
					sumc += 11
					print('Card played: A(11)\nSum: {}\n'.format(sumc))
			else:
				if power == 10:	
					sumc -= 10
					print('Card played: 10\nSum: {}\n'.format(sumc))
				elif power == 11 or power == 12:
					sumc += 10
					if power == 11:
						print('Card played: J\nSum: {}\n'.format(sumc))
					else:
						print('Card played: Q\nSum: {}\n'.format(sumc))
				else:
					sumc = 99
					if power == 13:
						print('Card played: K\nSum: {}\n'.format(sumc))
					else:
						print('Card played: Joker\nSum: {}\n'.format(sumc))
		b_replace_card(power)
	else:
		played = False #did bot play yet?
		for i in bcard:
			if i in nums and i + sumc <= 99:
				sumc += i
				print('Card played: {}\nSum: {}\n'.format(i, sumc))
				played = True
		if not played:
			if sumc + 10 <= 99:
				if 11 in bcard or 12 in bcard:
					sumc += 10
					if 11 in bcard:
						i = 11
						print('Card played: J\nSum: {}\n'.format(sumc))
					else:
						i = 12
						print('Card played: Q\nSum: {}\n'.format(sumc))
					played = True
		if not played:
			if 1 in bcard and sumc < 99:
				sumc += 1
				print('Card played: A(1)\nSum: {}\n'.format(sumc))
			else:
				if 13 in bcard or 14 in bcard:
					sumc = 99
					if 13 in bcard:
						i = 13
						print('Card played: K\nSum: {}\n'.format(sumc))
					else:
						i = 14
						print('Card played: Joker\nSum: {}\n'.format(sumc))
				elif 4 in bcard:
					i = 4
					print('Card played: 4\nSum: {}\n'.format(sumc))
				elif 9 in bcard:
					i = 9
					print('Card played: 9\nSum: {}\n'.format(sumc))
				elif 10 in bcard:
					sumc -= 10
					i = 10
					print('Card played: 10\nSum: {}\n'.format(sumc))
				else:
					print('Bot cards:\n')
					for i in bcard: #print cards
						if i == 1:
							print('[A]', end = '')
						elif i == 11:
							print('[J]', end = '')
						elif i == 12:
							print('[Q]', end = '')
						elif i == 13:
							print('[K]', end = '')
						elif i == 14:
							print('[Joker]', end = '')
						else:
							print('[{}]'.format(i), end = '')
					raise SystemExit('\n\nYou win!')
		b_replace_card(i)
				
##turn test
def play(n):
	if n == 0:
		bot() 
	else:
		player()

#gameplay
inpt = input('Do you want to go first?\n') #add difficulties later
if inpt != '':
	inpt = inpt[0]
if inpt == 'y' or inpt == 'Y':
	inpt = 0 
else:
	inpt = 1 
while True:
	inpt += 1
	play(inpt % 2)
	if cardl == []: #if cards all used up recycle deck
		for i in range(1, 14): #TODO work on making recycled deck not have duplicates
			for k in range(4):
				cardl.append(i)
		for i in range(2):
			cardl.append(14)
