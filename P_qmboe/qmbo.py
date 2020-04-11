#imports
import random
import os
import datetime
import qmbop

#vars
inpt = ''
p = ''

#dictonaries
#TODO R: finish long dictionary
convert = { ' ': '00',
			'a': '01',
            'b': '02',
            'c': '03',
            'd': '04',
            'e': '05',
            'f': '06',
            'g': '07',
            'h': '08',
            'i': '09',
            'j': '10',
            'k': '11',
            'l': '12',
            'm': '13',
            'n': '14',
            'o': '15',
            'p': '16',
            'q': '17',
            'r': '18',
            's': '19',
            't': '20',
            'u': '21',
            'v': '22',
            'w': '23',
            'x': '24',
            'y': '25',
            'z': '26'}

#user def functions
#encryption and decryption and more actions
def init():
	exit = 0;
	while(exit != 1):
		inpt = input(">action?\n");
		print("\n"*100+">>>"+inpt+"<<<"+"\n"*10);
		if(inpt == "<admint.del(log)>"):
			delLog();
		elif(inpt == "<admint.del(burgler-alarm)>"):
			delBurg();
		elif(inpt == "thank you"):
			exit = 1;
		elif inpt == '<admint.message(encrypt)>':
			encrypt()
		elif inpt == '<admint.message(decrypt)>':
			decrypt()
		else:
			print("Unexpected Input!");																										
	return "Success: Exit code 1"; #u exited the loop
#del log
def delLog():
	conf = input("Delete 'logue'? It will be gone for a very long time!") #Minecraft refrence here
	if(conf == "true"):
		os.remove("log.txt");
		logF = open("log.txt","a");
		logF.write(tt+"\n");
		logF.close();
		print("\n"*100);
		print("File has been deleted!")
	else:
		print("Error: Code leaf");
#del burg alarm
def delBurg():
	conf = input("Delete 'sD.txt'?")
	if(conf == "true"):
		os.remove("sD.txt");
		logL = open("sD.txt","w");
		logL.write("");
		logL.close();
		print("\n"*100);
		print("File has been deleted!")
	else:
		print("Error: Code leaf");
#encrypt 
def encrypt(): #TODO R: encrypt
	pass
#decrypt
def decrypt(): #TODO R: decrypt
	pass

#not in function
for i in range(1, 4):
	if i == 1:
		p = qmbop.qmboone()
	elif i == 2:
		p = qmbop.qmbotwo()
	else:
		p = qmbop.qmbothree()
	if (p == False):
		print("\n"*10);
		qmbotump = (str(datetime.datetime.now()),", failed at level: ",str(i),"\n")
		qmbotump = "".join(qmbotump);
		logL = open("sD.txt","a");
		logL.write(qmbotump); #yessir!
		logL.close();
		logA = open("Atpwd.txt","a");
		logA.write(qmbotump);
		logA.close();
		raise SystemExit('Access denied');
print("\n"*100);
tt = str(datetime.datetime.now());
print(">>===Welcome back, Cowlander===<<\n>>=logged in at "+tt+"=<<\n");
logF = open("log.txt","a");
logF.write(tt+":full login successful\n"); #kk ruoyu finished
logF.close();
logA = open("Atpwd.txt","r");
print("someone tried to log in at: \n");
print(logA.read());
logA.close();
logA = open("Atpwd.txt","w");
logA.write("");
logA.close();
#accidentily removed ATPWD but fixed
print(init());	


