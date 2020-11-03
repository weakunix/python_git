'''
Why the poacher?
because the poacher is the best!

WHY?
-it filters out expired deals
-it filters out deals with less than -5 ratings (todo)
-ad free
-FREE & MIT (the ™ and ©  are fake)
-it is a terminal friendly experiance
-auto-logs deals to file with date name and query
-compatable with these systems!
    -Windows
    -MacOS
    -Linux
    -IOS via Pythonista
    -boomers (developed in 1958!)

Anyways if you are seeing this from your local disk:
Thank you for choosing DealPoacher, and lets save some...
BUCKS. (get it? bucks? poaching? ok Imma stop before you uninstall)
'''
from bs4 import BeautifulSoup
import requests
import os
import datetime
from data import filehandler
import math
import time
import platform

def logo():
    for i in range(100):
        time.sleep(0.001)
        clearScreen()#logo pls ignore
        ii = i % 90
        print(f"""
{" " * ii}________                .__ __________                   .__                  TM
{" " * ii}\______ \   ____ _____  |  |\______   \_________    ____ |  |__   ___________ 
{" " * ii} |    |  \_/ __ \\__  \  |  | |     ___/  _ \__  \ _/ ___\|  |  \_/ __ \_  __ 
{" " * ii} |    `   \  ___/ / __ \|  |_|    |  (  <_> ) __ \\  \___|   Y  \  ___/|  | \/
{" " * ii}/_______  /\___  >____  /____/____|   \____(____  /\___  >___|  /\___  >__|   
{" " * ii}        \/     \/     \/                        \/     \/     \/     \/       
{" " * ii}                                      Designed & Developed in Cowland Software Technologies Lab™  ©1958 (yea right python wasn't even invented yet)""")

def clearScreen():
    os.system('clear' if os.name =='posix' else 'cls')
    print("\n"*100) #just in case

def printFirstPage(isFile = False):
    dealstuff = []
    deal, link = frontpage()
    clearScreen()
    for item in range(len(deal)): 
        if deal[item].replace(" ", "") != "":
            if isFile:
                dealstuff.append("| Deal | " + deal[item] + " | " + link[item] + " |")
            else:
                print("| Deal | " + deal[item] + " | " + link[item] + " |")
                print("=----<=>----=")
    return dealstuff

def query(q):
    dealName, dealLink, dealPostedTime = [], [], []
    req = "https://slickdeals.net/newsearch.php?page=1&src=SearchBarV2&q=" + str(q).replace(" ", "+")
    site = BeautifulSoup(requests.get(str(req)).content, 'html.parser')
    
    for item in site.find_all("p", {"class" : "head"}):
        if item.get_text() == ("We found no results for "+str(q)+", please try again."):
            return False #if there isn't any results for the  specified query
    
    items = BeautifulSoup(requests.get(str(req)).content, 'html.parser').find_all("div", {"class":"dealWrapper"})

    for y in range(len(items)):
        dealnames = items[y].find_all("a", href = lambda href: href and "/f/" in href and "/forums/" not in href)
        for deal in dealnames:
            dealName.append(deal.get_text())
            dealLink.append(deal["href"].replace("/f/", "https://slickdeals.net/f/").replace("/coupons/", "https://slickdeals.net/coupons/"))
    
    for i in range(len(items)):
        dealPosted = items[i].find_all("div", {"class":"dealInfo"})
        for deal in dealPosted:
            dealPostedTime.append(deal.find("div").get_text().replace("  ", ""))

    return dealName, dealLink, dealPostedTime #return the site queried

def frontpage():
    sickDeals, sickLinks = [], []
    site = BeautifulSoup(requests.get("https://slickdeals.net").content, 'html.parser').find_all("div", {"class" : "itemImageLink"})
    for i in range(len(site)):
        deals = site[i].find_all("a", href=True)#find every deal per every site
        for deal in deals:
            sickDeals.append(deal.get_text()) #from every deal get the text
            sickLinks.append(deal["href"].replace("/f/", "https://slickdeals.net/f/").replace("/coupons/", "https://slickdeals.net/coupons/"))
    return sickDeals, sickLinks #give back the array

def fp():
    printFirstPage()
    if input("\n\n>>>save? (Y/N)\n>>>")[0].lower() == "y":
        with open("./savedlist/deal_of_"+str(datetime.datetime.now()).replace(" ","_")+".txt", "w+") as f:
            for timedDeal in printFirstPage(True):
                f.write(timedDeal + "\n")

def consoleEdition():
    
    if datetime.datetime.now().timestamp() - float(filehandler.yamlload("./data/settings.yaml")["LastLog"]) > 8.64e+7: #if a day has passed then show frontpage deals
        fp()
    filehandler.yaml_it("./data/settings.yaml", "LastLog", str(datetime.datetime.now().timestamp())) #stamp now login time
    while True:
        clearScreen()
        command = input("Welcome to dealpoacher (not slickdeals ahem)\n Command list: \n type 'q' to quit\n type 'f' to display frontpage deals \n type 's item' to search all deals for item! \n>>>")
        if command[0] == "q":
            break
        elif command[0] == "f":
            fp()
        elif command[0] == "s":
            clearScreen()
            q = query(command[2:]) 
            if q != False:
                deal, link, times = q
                dealstuff = []
                item = 0
                while item < len(deal if len(deal) == len(link) == len(times) else ""):
                    if deal[item].replace(" ", "") != "" and "Expired" not in times[item]:
                        dealstuff.append("| Deal | " + deal[item] + " | " + times[item] + " | " + link[item] + " |")
                        print(dealstuff[item])
                        print("=----<=>----=")
                        item += 1
                if input("\n\n>>>save? (Y/N)\n>>>")[0].lower() == "y":
                    with open("./savedlist/deal_"+str(command[2:]).replace(" ","_")+"_"+str(datetime.datetime.now()).replace(" ","_")+".txt", "w+") as f:
                        for timedDeal in dealstuff:
                            f.write(timedDeal + "\n")
            else:
                input(f"\n We are sorry, but there doesn't seem to be any great results for '{str(command[2:])}' ... Check your spelling and capitalization. :( \n\n Enter to continue...")
    clearScreen()
    logo()
    print("Dealpoacher™ has been closed. You may now exit. \n\n THANK YOU FOR CHOOSING Dealpoacher™!\n\n ASCII art by (http://patorjk.com/software/taag/#p=display&f=Graffiti&t=DealPoacher) \n\n\n Check out other apps by Cowland Software Technologies Lab™ \n [Bingternet]()")

def mobileEdition():
    '''
    SHORTCUTS = [
    {'title': 'New Email', 'url': 'mailto:', 'color': '#5e96ff', 'icon': 'iow:email_24'},
    {'title': 'New Message', 'url': 'sms://', 'color': '#5ec0ff', 'icon': 'iow:chatbox_24'},
    {'title': 'Pythonista', 'url': 'pythonista3://', 'color': '#45d3e8', 'icon': 'iow:chevron_right_24'},
    {'title': 'Forum', 'url': 'http://forum.omz-software.com', 'color': '#4dd19d'},
    {'title': 'Google', 'url': 'http://google.com', 'color': '#a9de31'},
    {'title': 'DuckDuckGo', 'url': 'http://duckduckgo.com', 'color': '#ffd026' },
    {'title': 'Amazon', 'url': 'http://amazon.com', 'color': '#ff8e13'},
    {'title': 'eBay', 'url': 'http://ebay.com', 'color': '#ff4a09'},
    ]
    '''
    from versions import mobile, mobileWidget
    deal, link = frontpage()
    shortcuts = []
    for item in range(len(deal) if len(deal) == len(link) else len("")):
        if deal[item] != "" and link[item] != "":
            shortcuts.append({"title":str(deal[item]), "url": str(link[item]), "color": "#5e96ff"})
    mobileWidget.shortCut(shortcuts)
    mobileWidget.main()
    print("Widget Creation Successful!")
    
def winEdition():
    pass

def macEdition():
    pass

def main():
    if platform.machine().startswith("iP"):
        mobileEdition()
    elif os.name == "darwin":
        macEdition()
    elif os.name == "posix":
        winEdition()
    else:
        consoleEdition()


if __name__ == '__main__':
    logo()
    time.sleep(1)
    main() #start the deal hunt!
