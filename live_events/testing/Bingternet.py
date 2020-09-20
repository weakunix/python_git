import requests
from bs4 import BeautifulSoup
import re
import random
import os
import time
import datetime

def clear():
    if os.name == 'nt': 
        os.system('cls') 
    else: 
        os.system('clear')

version = "1.0"
engine = [
    "google",
    "bing",
    "yahoo",
    "duckduckgo"
]
usedEngine = 0

clear()

def logo():
    print("""
    __________.__                __                              __   
    \______   \__| ____    _____/  |_  ___________  ____   _____/  |_ 
    |    |  _/  |/    \  / ___\   __\/ __ \_  __ \/    \_/ __ \   __
    |    |   \  |   |  \/ /_/  >  | \  ___/|  | \/   |  \  ___/|  |  
    |______  /__|___|  /\___  /|__|  \___  >__|  |___|  /\___  >__|  
            \/        \//_____/           \/           \/     \/     

    V"""+str(version)+""" BINGVELOPED BY COWLAND TO RUOYU BECAUSE HE NEVER LEAVES THE TERMINAL ASDFDASFHJADHKASH
    """)

print("\033[1;32m Welcome back. Date is: " + str(datetime.datetime.now()))
logo()
query = str(input("\nCommand? ('halp' for tutorial): \n\n>>>"))

link = "https://www.google.com/search?q="

while True:
    clear()
    if 'halp' == query.split()[0]:
        print(
        """
        <Help>:
            <version>
                Bingternet V """ + str(version) +"""
            <commands>
                change [new search engine] (DuckDuckGo, Google, Bing, Yahoo)
                search [content] (searches for the content on your default search engine google if you didnt choose)
                back (goes back)
                forward (goes forward)
                close/exit/stop (exits the app)
        </Help>
        """
        )
        a = input("\n Press enter to continue...")
    elif 'search' == query.split()[0]:
        query = query.replace("search", "")
        qurry = str(link)+str(query)
        for i in range(50):
            time.sleep(0.005) #gives the server some time to rest
            clear()
            print(f"[< back] [forward >] [{str(qurry)}]")
            print("Searching for" + str(query) + " on " + str(engine[usedEngine]) + "\nElapsed : |" + ("█" * i) + (" " * (50 - i - 1 ) + "| ") + str(( i + 1) * 2) + "%")
        parafoRegExed = str(BeautifulSoup(requests.get(qurry).content, 'html.parser').prettify())
        parafoRegExed = re.sub("</span>", "", str(re.sub("<span>","",parafoRegExed))) #gets rid of spans
        for i in range(5):
            parafoRegExed = re.sub(f"</h{str(i)}>", "", str(re.sub(f"<h{str(i)}>","",parafoRegExed))) 

        a = []
        tagged = False
        for i in parafoRegExed:
            if i == "<" and tagged == False:
                a = []
                a.append(i)
                tagged = True
            elif i == ">" and tagged == True:
                a.append(i)
                tagged = False
                b = "".join(a)
                parafoRegExed = parafoRegExed.replace(b, "")
            elif i != ">" and i != "<" and tagged == True:
                a.append(i)
        parafoRegExed = parafoRegExed.split(" ")
        for i in range(len(parafoRegExed)):
            if parafoRegExed[i] == "<footer>":
                print("found footer!")
        i = 0
        while i < len(parafoRegExed):
            print(parafoRegExed[i])
            if parafoRegExed[i] == "Sign":
                break
            i += 1 #'''
        for i in range(len(parafoRegExed) - i):
                parafoRegExed.pop(0) 
        parafoRegExed = "".join(parafoRegExed)
        #input("" + parafoRegExed + "============================Results=Provided=By=Bingternet===========================\n\nEnter to continue...")
    elif "change" == query.split()[0]:
        query = query.replace("change ", "").lower()
        if query in engine:
            link = f"https://www.{query}.com/search?q="
            usedEngine = engine.index(query)
        input("You have changed your search engine to: "+str(query)+"!\n\nEnter to continue...") 
    elif "close" == query.split()[0] or "exit" == query.split()[0] or "stop" == query.split()[0]:
        clear()
        print("\033[0;37;40m Bingternet has been closed. You may now exit. \n\n THANK YOU FOR CHOOSING BINGTERNET!\n\n") 
        break
    clear()
    logo()
    query = str(input("\n>>>"))

