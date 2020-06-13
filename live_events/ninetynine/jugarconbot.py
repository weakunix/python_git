#imports
import random

#vars
cardl = [] #cards left
sumc = 0 #sum of cards
cardn = 0 #amount of cards per player
bcard = [] #bot cards
pcard = [] #player cards
bplay = False #did the bot already play?
inpt = '' #input
num = ['2', '3', '4', '5', '6', '7', '8', '9', '10'] #number cards

#filling cardl
for i in range(1, 14):
	for k in range(4):
		cardl.append(i)
for i in range(2):
	cardl.append(14)
	
#ask if it is first time playing
inpt = input('Is this your first time playing 99?\n')
if inpt != '':
	inpt = inpt[0] #setting input to first letter if input is not enter
if inpt == 'y' or inpt == 'Y': #need tutorial
	inpt = input('Objective of game: Get to 99 but don\'t go over. Make the other person go over 99 to win\n\nHow to play: When you play a card it adds to the sum of all the cards. For example if the first card played was 6 and the second card played was 3, the sum would be 9\n\nCard values:\nA: 1 or 11 (your choice)\n2: 2\n3: 3\n4: 0\n5: 5\n6: 6\n7: 7\n8: 8\n9: 0\n10: -10\nJ: 10\nQ: 10\nK: Automatically to 99\nJoker: Automatically to 99\n\nEnter to continue:\n') #print tutorial

#ask for amount of cards per player
while True:
	cardn = input('How many cards per player?\n')
	try: #trying to set input to integer
		cardn = int(cardn)
		break
	except:
		print('Input was not an integer\n')

#giving player cards
for i in range(cardn):
	pcard.append(cardl.pop(random.randint(1, len(cardl))))
	
#giving bot cards
for i in range(cardn):
	bcard.append(cardl.pop(random.randint(1, len(cardl))))

#ask for who goes first
inpt = input('Do you want to go first?\n')
if inpt != '':
	inpt = inpt[0] #setting input to first letter if input is not enter
if inpt != 'y' or inpt != 'Y': #bot goes first
	print(bcard)
	bplay = False
	for i in range(5):
		if bcard[i] != 1 and bcard[i] != 4 and bcard[i] != 9 and bcard[i] != 10 and bcard != 13 and bcard != 14:
			if bcard[i] == 11 or bcard[i] == 12:
				sumc += 10
				bplay = True
				if bcard[i] == 11:
					print('Card played: J\nSum: {}'.format(sumc))
				else:
					print('Card played: Q\nSum: {}'.format(sumc))
				bcard.pop(i)
				break
			else:
				sumc += bcard[i]
				print('Card played: {}\nSum: {}'.format(bcard[i], sumc))
				bplay = True
				bcard.pop(i)
				break
	if not bplay:
		i = random.randint(0, )
		inpt = bplay[i]
		if inpt == 13 or inpt == 14:
			sumc = 99
			if inpt == 13:
				print('Card played: K\nSum: {}'.format(sumc))
			else:
				print('Card played: Joker\nSum: {}'.format(sumc))
		elif inpt == 1:
			inpt = random.randint(1, 2)
			if inpt == 1:
				sumc += 1
				print('Card played: A(1)\nSum: {}'.format(sumc))
			else:
				sumc += 11
				print('Card played: A(11)\nSum: {}'.format(sumc))
		elif inpt == 10:
			sumc -= 10
			print('Card played: 10\nSum: {}'.format(sumc))
		else:
			if inpt == 4:
				print('Card played: 4\nSum: {}'.format(sumc))
			else:
				print('Card played: 9\nSum: {}'.format(sumc))
		bcard.pop(i)
		bcard.append(cardl.pop(random.randint(1, len(cardl))))

#game
while True:
	for i in pcard:
		if i == 1:
			print('[A]')
		elif i == 11:
			print('[J]')
		elif i == 12:
			print('[Q]')
		elif i == 13:
			print('[K]')
		elif i == 14:
			print('[Joker]')
		else:
			print('[{}]'.format(i))
	while True:
		inpt = input('Which card do you want to play?\n')
		if inpt[0] == 'a' or inpt[0] == 'A':
			if 1 in pcard:
				while True:
					inpt = input('1 or 11?\n')
					if inpt == '1':
						sumc += 1
						break
					elif inpt == '11':
						sumc += 11
						break
					else:
						print('{} is not an option'.format(inpt))
				break
		elif inpt[0] == 'j' or inpt[0] == 'J':
			if inpt[1] == 'a' or inpt[1] == 'A':
				if 11 in pcard:
					sumc += 10
					break
			elif inpt[1] == 'o' or inpt[1] == 'O':
				if 14 in pcard:
					sumc = 99
					break
		elif inpt[0] == 'q' or inpt[0] == 'Q':
			if 12 in pcard:
				sumc += 10
				break
		elif inpt[0] == 'k' or inpt[0] == 'K':
			if 13 in pcard:
				sumc = 99
				break
		elif inpt in num:
			inpt = int(inpt)
			if inpt in pcard:
				sumc += inpt
				break
		else:
			print('{} does not exist or you don\'t have {} in your hand'.format(inpt, inpt))
	bplay = False
	for i in range(5):
		if bcard[i] != 1 and bcard[i] != 4 and bcard[i] != 9 and bcard[i] != 10 and bcard != 13 and bcard != 14:
			if bcard[i] == 11 or bcard[i] == 12:
				sumc += 10
				bplay = True
				if bcard[i] == 11:
					print('Card played: J\nSum: {}'.format(sumc))
				else:
					print('Card played: Q\nSum: {}'.format(sumc))
				bcard.pop(i)
				break
			else:
				sumc += bcard[i]
				print('Card played: {}\nSum: {}'.format(bcard[i], sumc))
				bplay = True
				bcard.pop(i)
				break
	if not bplay:
		i = random.randint(0, )
		inpt = bplay[i]
		if inpt == 13 or inpt == 14:
			sumc = 99
			if inpt == 13:
				print('Card played: K\nSum: {}'.format(sumc))
			else:
				print('Card played: Joker\nSum: {}'.format(sumc))
		elif inpt == 1:
			inpt = random.randint(1, 2)
			if inpt == 1:
				sumc += 1
				print('Card played: A(1)\nSum: {}'.format(sumc))
			else:
				sumc += 11
				print('Card played: A(11)\nSum: {}'.format(sumc))
		elif inpt == 10:
			sumc -= 10
			print('Card played: 10\nSum: {}'.format(sumc))
		else:
			if inpt == 4:
				print('Card played: 4\nSum: {}'.format(sumc))
			else:
				print('Card played: 9\nSum: {}'.format(sumc))
		bcard.pop(i)
		bcard.append(cardl.pop(random.randint(1, len(cardl))))
