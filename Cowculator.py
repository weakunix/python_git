#imports
import numpy as np
import re
import random

#vars
tutorial="no"
use="yes"
allans=[0]
ans=0
guess=""
numexpr=re.compile(r"([.\d]+|ans)\s*([^.\d]+)\s*([.\d]+|ans)")
n=""
hints=["moo", "everyday", "op", "nai", "belt"]
passwords=["cow", "albreto", "747", "bing", "workhorse"]
password=""
hint=""
version="v3.5"
inc="no"

#game vars
played=0
name=""
money=1000
fuel=10
cessna=1
embraer=0
a320=0
b777=0
b747=0
a380=0
concorde=0
autopilot=0
factory=0

#main
print("Welcome to the Cowculator!\n")
tutorial=input("Is this your first time using the Cowculator? (yes/no)\n")
if tutorial=="yes":
    print("How to use:\nType in the problem that you want the Cowculator to solve and it will give you the answer.\n")
    tutorial=input("Press enter to continue:\n")
    print("Cowculator {} only supports 2 numbers so if you use more than 2 numbers you will recieve an error.\n".format(version))
    tutorial=input("Press enter to continue:\n")
    print("Also keep in mind that Cowculator {} supports the ans function.\nIf you would like to use your previous answer, type in 'ans'.\nFor example, I can type in '1+1' and the Cowculator would print '2'\nThen I can type in 'ans+1' and the Cowculator would print 3.\n".format(version))
    tutorial=input("Press enter to continue:\n")
    print("You can use integers and decimals.\nFractions are not supported on Cowculator {}.\nIf you would like to cowculate fractions, first convert them into decimals.\nFor example, to convert 1/2 I would type '1/2' into the Cowculator to get the decimal 0.5.\n".format(version))
    tutorial=input("Press enter to continue:\n")
    print("Cowculator {} also does not support negative numbers.\nThis will be coming out as soon as possible.\n".format(version))
    tutorial=input("Press enter to continue:\n")
    print("To end the program, type in 'end' when the Cowculator asks for the problem.\n")
    tutorial=input("Press enter to continue:\n")
    print("If you need any help, type in 'help'.\n")
    tutorial=input("Press enter to continue:\n")
    print("There is a hidden function inlcuded in Cowculator {}. Try to find it!\n".format(version))
    tutorial=input("Press enter to continue:\n")
    print("If the Cowculator is taking too long, use control c (ctrl+c) to terminate the program.\n")
    tutorial=input("Press enter to continue:\n")
    print("The current functions on the Cowculator {} are:\nAddition: + (i.e. 1+1)\nSubtraction: - (i.e. 2-1)\nMultiplication: * (i.e. 2*3)\nDivision: / (i.e. 4/2)\n".format(version))
    tutorial=input("Press enter to continue:\n")
    print("Module: % (i.e. 6%4)\nExponents: ^ (i.e. 2^3)\nSquare Root: sqrt() (i.e. sqrt(4))\nFactorials: !(i.e. 3!)\n")
    tutorial=input("Press enter to continue:\n")
    print("Prime Factorization: pf() (i.e. pf(12))\nGreatest Common Factor: gcf(,) (i.e. gdf(10,6))\nLeast Common Multiple: lcm(,) (i.e. lcm(4,6))\nSimplify Fractions: sim() (i.e. sim(4/6))\n")
    tutorial=input("Press enter to continue:\n")
    print("Decimal to Fraction Conversion: con() (i.e. con(2.45))\nRepeating Decimal to Fraction Conversion: conr() (i.e. conr(1.3) (Which would be 1.3333333333...))\n")
    tutorial=input("Press enter to continue:\n")
print("Type in the problem:", end="")
while n!="end":
    inc="no"
    n=input("\n") #input
    a=""
    o=""
    b=""
    m=numexpr.match(n)
    if n=="end":
        break
    elif n=="help":
        inc="yes"
        print("How to use:\nType in the problem that you want the Cowculator to solve and it will give you the answer.\n")
        tutorial=input("Press enter to continue:\n")
        print("Cowculator {} only supports 2 numbers so if you use more than 2 numbers you will recieve an error.\n".format(version))
        tutorial=input("Press enter to continue:\n")
        print("Also keep in mind that Cowculator {} supports the ans function.\nIf you would like to use your previous answer, type in 'ans'.\nFor example, I can type in '1+1' and the Cowculator would print '2'\nThen I can type in 'ans+1' and the Cowculator would print 3.\n".format(version))
        tutorial=input("Press enter to continue:\n")
        print("You can use integers and decimals.\nFractions are not supported on Cowculator {}.\nIf you would like to cowculate fractions, first convert them into decimals.\nFor example, to convert 1/2 I would type '1/2' into the Cowculator to get the decimal 0.5.\n".format(version))
        tutorial=input("Press enter to continue:\n")
        print("Cowculator {} also does not support negative numbers.\nThis will be coming out as soon as possible.\n".format(version))
        tutorial=input("Press enter to continue:\n")
        print("To end the program, type in 'end' when the Cowculator asks for the problem.\n")
        tutorial=input("Press enter to continue:\n")
        print("If you need any help, type in 'help'.\n")
        tutorial=input("Press enter to continue:\n")
        print("There is a hidden fucntion inlcuded in Cowculator {}. Try to find it!\n".format(version))
        tutorial=input("Press enter to continue:\n")
        print("If the Cowculator is taking too long, use control c (ctrl+c) to terminate the program.\n")
        tutorial=input("Press enter to continue:\n")
        print("The current functions on the Cowculator {} are:\nAddition: + (i.e. 1+1)\nSubtraction: - (i.e. 2-1)\nMultiplication: * (i.e. 2*3)\nDivision: / (i.e. 4/2)\n".format(version))
        tutorial=input("Press enter to continue:\n")
        print("Module: % (i.e. 6%4)\nExponents: ^ (i.e. 2^3)\nSquare Root: sqrt() (i.e. sqrt(4))\nFactorials: !(i.e. 3!)\n")
        tutorial=input("Press enter to continue:\n")
        print("Prime Factorization: pf() (i.e. pf(12))\nGreatest Common Factor: gcf(,) (i.e. gdf(10,6))\nLeast Common Multiple: lcm(,) (i.e. lcm(4,6))\nSimplify Fractions: sim() (i.e. sim(4/6))\n")
        tutorial=input("Press enter to continue:\n")
        print("Decimal to Fraction Conversion: con() (i.e. con(2.45))\nRepeating Decimal to Fraction Conversion: conr() (i.e. conr(1.3) (Which would be 1.3333333333...))\n")
        tutorial=input("Press enter to continue:\n")
        print("Type in the problem:", end="")
    elif n=="": #Enter/Clear History
        inc="yes"
        print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nType in the problem:", end="")
    elif n=="ans": #Answers
        inc="yes"
        print("Your previous answer was {}.\nAll of your answers are {}".format(ans, allans))
    elif n[:4]=="sqrt": #Square Root
        a=n[5:-1]
        if a=="ans":
            a=ans
        else:
            a=float(a)
        ans=np.sqrt(a)
        print(ans)
    elif n[-1]=="!": #Factorials
        a=n[:-1]
        if a=="ans":
            a=int(ans)
        else:
            a=int(a)
        ans=1
        for i in range(1, a+1):
            ans*=i
        print(ans)
    elif n[:2]=="pf": #Prime Factorization
        a=n[3:-1]
        if a=="ans":
            a=int(ans)
        else:
            a=int(a)
        if a==1:
            print(1)
        for i in range(2,a+1):
            while a%i==0:
                print("{} ".format(i), end="")
                a=a/i
        print("")
    elif n[:3]=="gcf": #Greatest Common Factor
        ans=1
        c=4
        for i in n[5:-1]:
            c+=1
            if i==",":
                break
        a=n[4:c]
        b=n[c+1:-1]
        if a=="ans":
            a=int(ans)
        else:
            a=int(a)
        if b=="ans":
            b=int(ans)
        else:
            b=int(b)
        if a<b:
            for i in range(2, a+1):
                if a%i==0 and b%i==0:
                    ans=i
        else:
            for i in range(2, b+1):
                if a%i==0 and b%i==0:
                    ans=i
        print(ans)
    elif n[:3]=="lcm": #Least Common Multiple
        gcf=1
        c=4
        for i in n[5:-1]:
            c+=1
            if i==",":
                break
        a=n[4:c]
        b=n[c+1:-1]
        if a=="ans":
            a=int(ans)
        else:
            a=int(a)
        if b=="ans":
            b=int(ans)
        else:
            b=int(b)
        if a==1 or b==1:
            print(1)
        elif a<b:
            for i in range(2, a+1):
                if a%i==0 and b%i==0:
                    gcf=i
        else:
            for i in range(2, b+1):
                if a%i==0 and b%i==0:
                    gcf=i
        ans=a*b/gcf
        print(ans)
    elif n[:3]=="sim": #Simlify Fractions
        gcf=1
        c=4
        for i in n[5:-1]:
            c+=1
            if i=="/":
                break
        a=n[4:c]
        b=n[c+1:-1]
        if a=="ans":
            a=int(ans)
        else:
            a=int(a)
        if b=="ans":
            b=int(ans)
        else:
            b=int(b)
        if a==1 or b==1:
            print(1)
        elif a<b:
            for i in range(2, a+1):
                if a%i==0 and b%i==0:
                    gcf=i
        else:
            for i in range(2, b+1):
                if a%i==0 and b%i==0:
                    gcf=i
        a/=gcf
        b/=gcf
        ans=a/b
        print("{}/{}".format(a, b))
    elif n[:4]=="con(": #Decimal to Fraction Conversion
        num=0
        n=n[4:-1]
        if n=="ans":
            n=str(ans)
        for i in n:
            if i==".":
                break
            else:
                num+=1
        a=n[:num]
        b=n[num+1:]
        n=1
        for i in range(1, len(b)+1):
            n*=10
        a=int(a+b)
        b=input("Do you want to simplify your fraction? (yes/no)\n")
        gcf=1
        if b=="yes":
            if a==1 or n==1:
                gcf=1
            elif a<n:
                for i in range(2, a+1):
                    if a%i==0 and n%i==0:
                        gcf=i
            else:
                for i in range(2, b+1):
                    if a%i==0 and n%i==0:
                        gcf=i
            a/=gcf
            n/=gcf
        ans=a/n
        print("{}/{}".format(a, n))
    elif n[:4]=="conr": #Repeating Decimal to Fraction Conversion
        num=0
        n=n[5:-1]
        if n=="ans":
            n=str(ans)
        for i in n:
            if i==".":
                break
            else:
                num+=1
        a=n[:num]
        b=n[num+1:]
        n=""
        for i in range(1, len(b)+1):
            n+="9"
        if n=="":
            n=1
        else:
            n=int(n)
        b=int(b)
        a=int(a)
        a=b+a*n
        b=input("Do you want to simplify your fraction? (yes/no)\n")
        gcf=1
        if b=="yes":
            if a==1 or n==1:
                gcf=1
            elif a<n:
                for i in range(2, a+1):
                    if a%i==0 and n%i==0:
                        gcf=i
            else:
                for i in range(2, n+1):
                    if a%i==0 and n%i==0:
                        gcf=i
            a/=gcf
            n/=gcf
        ans=a/n
        print("{}/{}".format(a, n))
    elif m is not None:
        a=m.group(1)
        o=m.group(2)
        b=m.group(3)
        if a=="ans":
            a=ans
        else:
            a=float(a)
        if b=="ans":
            b=ans
        else:
            b=float(b)
        
        if o=="+": #addition
            ans=a+b
            print(ans)
        elif o=="-": #subtraction
            ans=a-b
            print(ans)
        elif o=="*": #multiplication
            ans=a*b
            print(ans)
        elif o=="/": #division
            ans=a/b
            print(ans)
        elif o=="%": #mod
            ans=a%b
            print(ans)
        elif o=="^": #exponents
            ans=1
            b=int(b)
            for i in range(1, b+1):
                ans*=a
            print(ans)
    elif n=="enter game": #the hidden game :)
        inc="yes"
        if played==0:
            password=random.randint(0,4)
            hint=hints[password]
            password=passwords[password]
            print("Hint: {}".format(hint))
            guess=input("Password:\n")
            print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
            if guess==password:
                print("Welcome to plane simulator!\n")
                name=input("What is your company's name:\n")
                print("Grandpa: Hello {}! I have heard that you wanted to start a airline business. Well your in luck! I can give you my old Cessna Caravan I used back in the day and take 1000 dollars as well. Anyways, good luck!\n".format(name))
                n=input("Press enter to continue:\n")
                played=1
            else:
                break
        if name=="Cowland" or name=="cowland" or name=="MrMoooo" or name=="mrmoooo" or name=="Mootwbing" or name=="mootbing" or name=="Naibing" or name=="naibing" or name=="Conorito" or name=="conorito": #Nothing to see here :) ;)
            n=input("Do you want to enable cheats? (yes/no)\n")
            if n=="yes":
                money=int(input("How much money do you want?\n"))
                fuel=int(input("How much fuel do you want?\n"))
                print("Enjoy your cheats! :)\n")
        while n!="exit":
            n=input("Fly: Flies all of your current planes.\nShop: Buy fuel, new planes, or upgrades.\nCurrent status: Check how much money you have and which planes you have.\nExit: Exit game. Your progress will be saved unless you disconnect from the site.\n")
            if n=="fly": #fly
                beforemoney=money
                if autopilot==1:
                    n=int(input("How many times do you want to fly your planes? (1-10)\n"))
                    if n>10:
                        n=1
                else:
                    n=1
                for i in range(1, n+1):
                    fuel+=factory
                    n=concorde
                    while n!=0:
                        if fuel>=300:
                            p=random.randint(70, 100)
                            money+=100000*p
                            fuel-=300
                            n-=1
                        else:
                            break
                    n=a380
                    while n!=0:
                        if fuel>=130:
                            p=random.randint(650, 870)
                            money+=3000*p
                            fuel-=130
                            n-=1
                        else:
                            break
                    n=b747
                    while n!=0:
                        if fuel>=80:
                            p=random.randint(400, 600)
                            money+=2200*p
                            fuel-=80
                            n-=1
                        else:
                            break
                    n=b777
                    while n!=0:
                        if fuel>=50:
                            p=random.randint(280, 360)
                            money+=1500*p
                            fuel-=50
                            n-=1
                        else:
                            break
                    n=a320
                    while n!=0:
                        if fuel>=20:
                            p=random.randint(130, 180)
                            money+=700*p
                            fuel-=20
                            n-=1
                        else:
                            break
                    n=embraer
                    while n!=0:
                        if fuel>=5:
                            p=random.randint(50, 80)
                            money+=300*p
                            fuel-=5
                            n-=1
                        else:
                            break
                    n=cessna
                    while n!=0:
                        if fuel>=1:
                            p=random.randint(8, 10)
                            money+=100*p
                            fuel-=1
                            n-=1
                        else:
                            break
                print("You have {} fuel left.\nYou earned {} dollars.\nNow you have {} dollars.\n".format(fuel, money-beforemoney, money))
            elif n=="shop": #shop
                n=input("Fuel: 100\nCessna Caravan: 100,000 (Carries 10 passengers and uses 1 fuel to fly. Will need repair after 10 flights. Tickets cost 100.)\nEmbraer 175: 500,000 (Carries 80 passengers and uses 5 fuel to fly. Will need repair after 15 flights. Tickets cost 300.)\nA320: 2 million (Carries 180 passengers and uses 20 fuel to fly. Will need repair after 30 flights. Tickets cost 700.)\nB777: 7 million (Carries 360 passengers and uses 50 fuel to fly. Will need repair after 45 flights. Tickets cost 1,500.)\nB747: 15 million (Carries 600 passengers and uses 80 fuel to fly. Will need repair after 60 flights. Tickets cost 2,200.)\nA380: 30 million (Carries 870 passengers and uses 130 fuel to fly. Will need repair after 80 flights. Tickets are 3,000)\nConcorde: 50 million (Carries 100 passengers and uses 300 fuel to fly. Will need repair after 100 flights. Tickets cost 100,000.)\nAuto pilot: 40 million (Flies all planes automatically up to 20 times if you have enough fuel.)\nFactory: 20 million (Produces fuel every time you fly.)\nFactory upgrade: 15 million (Factory produced 1 more fuel everytime you fly.)\nExit: Exit the shop.\nYou have {} dollars.\n".format(money))
                if n=="fuel":
                    n=int(input("How much fuel do you want to buy?\n"))
                    if money>=n*100:
                        fuel+=n
                        money-=n*100
                        print("You purchased {} fuel.\n".format(n))
                    else:
                        print("Not enough money.\n")
                elif n=="Cessna Caravan":
                    n=int(input("How many Cessna Caravans do you want to buy?\n"))
                    if money>=n*100000:
                        cessna+=n
                        money-=n*100000
                        print("You purchased {} Cessna Caravan(s).\n".format(n))
                    else:
                        print("Not enough money.\n")
                elif n=="Embraer 175":
                    n=int(input("How many Embraer 175s do you want to buy?\n"))
                    if money>=n*500000:
                        embraer+=n
                        money-=n*500000
                        print("You purchased {} Embraer 175(s).\n".format(n))
                    else:
                        print("Not enough money.\n")
                elif n=="A320":
                    n=int(input("How many A320s do you want to buy?\n"))
                    if money>=n*2000000:
                        a320+=n
                        money-=n*2000000
                        print("You purchased {} A320(s).\n".format(n))
                    else:
                        print("Not enough money.\n")
                elif n=="B777":
                    n=int(input("How many B777s do you want to buy?\n"))
                    if money>=n*7000000:
                        b777+=n
                        money-=n*7000000
                        print("You purchased {} B777(s).\n".format(n))
                    else:
                        print("Not enough money.\n")
                elif n=="B747":
                    n=int(input("How many B747s do you want to buy?\n"))
                    if money>=n*15000000:
                        b747+=n
                        money-=n*15000000
                        print("You purchased {} B747(s).\n".format(n))
                    else:
                        print("Not enough money.\n")
                elif n=="A380":
                    n=int(input("How many A320s do you want to buy?\n"))
                    if money>=n*30000000:
                        a380+=n
                        money-=n*30000000
                        print("You purchased {} A380s.\n".format(n))
                    else:
                        print("Not enough money.\n")
                elif n=="Concorde":
                    n=int(input("How many Concordes do you want to buy?\n"))
                    if money>=n*50000000:
                        concorde+=n
                        money-=n*50000000
                        print("You purchased {} Concorde(s).\n".format(n))
                    else:
                        print("Not enough money.\n")
                elif n=="auto pilot":
                    if money>=40000000 and autopilot==0:
                        autopilot=1
                        money-=40000000
                        print("You have purchased auto pilot.\n")
                    elif autopilot==1:
                        print("You already have auto pilot. This can't be purchased twice.\n")
                    else:
                        print("Not enough money.\n")
                elif n=="factory":
                    if money>=20000000 and factory==0:
                        factory=1
                        money-=20000000
                        print("You have purchased a factory.\n")
                    elif factory!=0:
                        print("You already have a factory. This can't be purchased twice. If you want to make more fuel, buy the factory upgrade.\n")
                    else:
                        print("Not enough money.\n")
                elif n=="factory upgrade":
                    n=int(input("How many factory upgrades do you want?\n"))
                    if money>=15000000*n:
                        factory+=n
                        money-=15000000*n
                        print("You purchased {} factory upgrade(s).\n".format(n))
                    else:
                            print("Not enough money.\n")
                elif n=="exit":
                    print(" ", end="")
                    n=""
                else:
                    print("This is not a product in the shop. If you want to buy fuel, type in 'fuel'. If you want to buy a plane, be sure to capitalize the name (i.e. Cessna Caravan or Embraer 175)\n")
                print("You now have {} dollars.\n".format(money))
            elif n=="current status": #current status
                print("{} Cessna Caravan.\n{} Embraer 175.\n{} A320.\n{} B777.\n{} B747.\n{} A380.\n{} Concorde.\n{} dollars.\n{} fuel.\nFuel needed for all planes to fly once: {}".format(cessna, embraer, a320, b777, b747, a380, concorde, money, fuel, cessna+embraer*5+a320*20+b777*50+b747*80+a380*130+concorde*300))
            elif n=="exit": #exit
                print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nType in the problem:\n")
            else:
                print("Not valid command.")
            
    else:
        inc="yes"
        print("This is not a function on the Cowculator. If you need help, type in 'help'.\n")
    if inc!="yes":
        allans.append(ans)
print("Thank you for using the Cowculator!")
