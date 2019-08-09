import random

alpha="abcdefghijklmnopqrstuvwxyz"
cipher=""
current=0
message=input("What is the message?\n")
coded=""

for i in range(len(message)):
    current=random.randint(10,25)
    new=message[i]
    new=int(alpha.find(new))
    new+=current
    new=new%26
    new=alpha[new]
    coded+=new
    current=str(current)
    cipher+=current
print(coded)
print(cipher)
