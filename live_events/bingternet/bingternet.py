import requests
from bs4 import BeautifulSoup
from bs4.element import Tag
import re
import random
import webbrowser
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
    if 'halp' == query.split()[0] or 'help' == query.split()[0]:
        logo()
        print(
        """
<Help>
    <logo>
        Curtesey of [http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20]
    <version>
        Bingternet V """ + str(version) +"""
    <commands>
        <Search Engine Actions>
            SEchange [change search engine] (DuckDuckGo, Google, Bing, Yahoo)
            SEshow
        <Browser Actions>
            Search[S] [content/URL] (searches for the content on your default search browser. if you type 'S' at the end of 'search', it'll save the site (you can also save the site after it loads) )
                save (same as BsearchS but if you forgot u can do after site loads)
                open (opens site in browser)
            back (goes back)
            new (new tab)
            close (close all tabs)
            close (close current tab)
            newsaveloc [./foldername] (changes savig location of sites)
        < General>
            close/exit/stop (exits the app)
            rem (removes all saved html files)
</Help>
        """
        )
        a = input("\n Press enter to continue...")
    elif query.lower().startswith("search"):
        searchORSave = query.lower().startswith("searchs ")
        query = query.lower().replace("searchs ", "") if searchORSave else query.lower().replace("search ", "")
        query = query.replace(" ", "%20") #the word searched for
        qurry = str(link)+str(query)+"&num=5" #the actual link

        for i in range(100):
            time.sleep(0.0001) #gives the server some time to rest
            clear()
            print(f"[< bback] [{str(qurry)}] [|" + ("█" * (i // 10)) + (" " * (10 - (i//10) - 1 ) + "|") + str(( i + 1)) + "%] [X bclose]")
        soupOfHTML = BeautifulSoup(requests.get(qurry).content, 'html.parser')
        divider = soupOfHTML.find_all('div', class_='g')
        print(divider)
        def save():
            if searchORSave:
                print("======================Saving=site============================")
                try:
                    if not os.path.exists('./sites/'):
                        os.mkdir('./sites/')
                    with open(f'./sites/{datetime.datetime.now()}{query.replace("%20", " ")}.html', 'w+') as wr:
                            wr.write(soupOfHTML.prettify())
                    print("File saved to: " + str(os.getcwd()))
                except Exception as e:
                    print("ERROR SAVING WEBSITE!!! \n" + str(e))
        save()
        adcmd = input(
             "============================Results=Provided=By=Bingternet===========================\n\nAdditional Commands? (save, open) \n>>>"
        )
        if adcmd == "save":
            searchORSave = True
            save()
            input("Enter to continue...")
        elif adcmd == "open":
            webbrowser.open(str(qurry), autoraise=True)
            input(f"Opening \n[{qurry}] \n\nEnter to continue...")
    
    elif "SEchange" == query.split()[0]:
        query = query.replace("SEchange ", "").lower()
        if query in engine:
            link = f"https://www.{query}.com/search?q="
            usedEngine = engine.index(query)
            input("You have changed your search engine to: "+str(query)+"!\n\nEnter to continue...")
        else:
            input("Remember to include a space between 'SEchange engine'. Avaliable engines " + str(engine).replace("[","").replace("]",""))
    elif "close" == query.lower().split()[0] or "exit" == query.lower().split()[0] or "stop" == query.lower().split()[0]:
        for i in range(10):
            time.sleep(0.1)
            clear()
            print(f"""
 {" " * i * 2}   __________.__                __                              __   
 {" " * i * 2}   \______   \__| ____    _____/  |_  ___________  ____   _____/  |_ 
 {" " * i * 2}   |    |  _/  |/    \  / ___\   __\/ __ \_  __ \/    \_/ __ \   __
 {" " * i * 2}   |    |   \  |   |  \/ /_/  >  | \  ___/|  | \/   |  \  ___/|  |  
 {" " * i * 2}   |______  /__|___|  /\___  /|__|  \___  >__|  |___|  /\___  >__|  
 {" " * i * 2}           \/        \//_____/           \/           \/     \/     
        """)
            if i == 9:
                print(f"{' ' * i * 2}          ===============" + "Version: " + str(version) + "=============== \n\n\n")
            else:
                print((" " * ((50 - i) * 5)) + ("█" * (i * 5)))
        print("\033[0;34m Bingternet has been closed. You may now exit. \n\n THANK YOU FOR CHOOSING BINGTERNET!\n\n") 
        break
    clear()
    logo()
    query = str(input("\n>>>"))

