#imports
import random

#vars
password=""
run=1
pa=""

#lists
passwords=["mootbing","overprotective","jason","coding","leave","sporty","albreto","playdates","mac","weiner","raft"]
hints=["cow","mom","best cousin ever","nerdy","the word","expectacion","everyday","best","sucks","sport","poor green screen"]

pn=random.randint(0,10)
password=passwords[pn]
hint=hints[pn]
print("Hint: {}\n".format(hint))
pa=input("Password: ")
if pa==password:
    print("Access approved.\n")
    while run==1:
        access=input("Would you like to use cipher or decipher?\nType in \"end\" if you want to end the program.\n")
        if access=="cipher":
            alpha="abcdefghijklmnopqrstuvwxyz"
            cipher=""
            current=0
            message=input("What is the message?\n")
            coded=""
            for i in range(len(message)):
                current=random.randint(1,25)
                new=message[i]
                if new==" ":
                    coded+=" "
                    cipher+=" "
                else:
                    new=int(alpha.find(new))
                    new+=current
                    new=new%26
                    new=alpha[new]
                    coded+=new
                    current=alpha[current]
                    cipher+=current
            for i in range(1, 200):
                print("\n")
            print("Your ciphered message is {}.".format(coded))
            print("Your cipher is {}.\n".format(cipher))
        elif access=="decipher":
            alpha="abcdefghijklmnopqrstuvwxyz"
            current=""
            coded=input("What is the message?\n")
            cipher=input("What is the cipher?\n")
            decoded=""
            for i in range(len(coded)):
                current=cipher[i]
                current=int(alpha.find(current))
                current=int(current)
                new=coded[i]
                if new==" ":
                    decoded+=" "
                else:
                    new=int(alpha.find(new))
                    new-=current
                    new=new%26
                    new=alpha[new]
                    decoded+=new
            print("Your decoded message is {}.\n".format(decoded))
        elif access=="end":
            break
        else:
            print("This function does not exist. Type in \"cipher\" or \"decipher\".\n")
else:
    print("Access denied.\n")
