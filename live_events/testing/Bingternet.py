import requests
from bs4 import BeautifulSoup
import re
import random
import os

def clear():
    if os.name == 'nt': 
        os.system('cls') 
    else: 
        os.system('clear')

version = "1.0"
engine = [
    "Google",
    "Bing",
    "Yahoo",
    "DuckDuckGo"
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

    V"""+str(version)+""" BINGVELOPED BY COWLAND TO RUOYU BECAUSE HE NEVER FUCKING LEAVES THE TERMINAL ASDFDASFHJADHKASH
    """)

logo()
query = str(input("\nCommand? ('halp' for tutorial): \n\n>>>"))

while True:
    clear()
    if 'halp' == query.split()[0]:
        print(
        """
        <Help>:
            <version>
                Bingternet V """ + str(version) +"""
            <commands>
                changeEngine [new search engine] (DuckDuckGo, Google, Bing, Yahoo)
                search [content] (searches for the content on your default search engine google if you didnt choose)
                back (goes back)
                forward (goes forward)
                close (exits the app)
        </Help>
        """
        )
        a = input("\n Press enter to continue...")
    elif 'search' == query.split()[0]:
        query = query.replace("search", "")
        for i in range(random.randint(1, 5)):
            clear()
            print("Searching for" + str(query) + " on " + str(engine[usedEngine]) + ("."*i))
        parafoRegExed = str(BeautifulSoup(requests.get("https://www.google.com/search?q="+str(query)).content, 'html.parser').prettify())
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
        
        input(parafoRegExed + "============================Results=Provided=By=Bingternet===========================\n\nEnter to continue...")
    elif "close" == query.split()[0]:
        print("Bingternet has been closed. You may now exit. \n\n THANK YOU FOR CHOOSING BINGTERNET!\n\n") 
        break
    clear()
    logo()
    query = str(input("\n>>>"))

