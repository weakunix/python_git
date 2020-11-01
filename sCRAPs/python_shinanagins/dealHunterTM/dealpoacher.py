from bs4 import BeautifulSoup
import requests
import os
import datetime
from data import filehandler
import math
import time

def clearScreen():
    os.system('clear' if os.name =='posix' else 'cls')

def printFirstPage(isFile = False):
    dealstuff = []
    deal, link = frontpage()
    clearScreen()
    for item in range(len(deal)):
        if deal[item].replace(" ", "") != "":
            if isFile:
                dealstuff.append("|Deal| " + deal[item] + " |" + link[item] + "|")
            else:
                print("|Deal| " + deal[item] + " |" + link[item] + "|")
                print("=")
    return dealstuff

def query(q):
    req = "https://slickdeals.net/newsearch.php?src=SearchBarV2&q=" + q.replace(" ", "+")
    site = BeautifulSoup(requests.get(str(req)).content, 'html.parser')
    for item in site.find_all("p", {"class" : "head"}):
        if item.get_text() == ("We found no results for "+str(q)+", please try again."):
            return False #if there isn't any results for the  specified query
    
    return #return the site queried

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
    if input("\n\n>>>save? (Y/N)\n>>>")[0] == "y":
        with open("./savedlist/deal_of_"+str(datetime.datetime.now()).replace(" ","_")+".txt", "w+") as f:
            for timedDeal in printFirstPage(True):
                f.write(timedDeal + "\n")

def main():
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
            if query(command[2:]) != False:
                pass
            else:
                input(f"\n We are sorry, but there doesn't seem to be any great results for '{str(command[2:])}' ... Check your spelling and capitalization. :( \n\n Enter to continue...")
    clearScreen()
    for i in range(10):
        time.sleep(0.1)
        clearScreen()
        print(f"""
{" " * i * 2}________                .__ __________                   .__                  
{" " * i * 2}\______ \   ____ _____  |  |\______   \_________    ____ |  |__   ___________ 
{" " * i * 2} |    |  \_/ __ \\__  \  |  | |     ___/  _ \__  \ _/ ___\|  |  \_/ __ \_  __ 
{" " * i * 2} |    `   \  ___/ / __ \|  |_|    |  (  <_> ) __ \\  \___|   Y  \  ___/|  | \/
{" " * i * 2}/_______  /\___  >____  /____/____|   \____(____  /\___  >___|  /\___  >__|   
{" " * i * 2}        \/     \/     \/                        \/     \/     \/     \/       (http://patorjk.com/software/taag/#p=display&f=Graffiti&t=DealPoacher)
        """)
        if i == 9:
            print(f"{' ' * i * 2}          ===============" + "Version: " + str("1.0") + "=============== \n\n\n")
            print("Dealpoacher™ has been closed. You may now exit. \n\n THANK YOU FOR CHOOSING Dealpoacher™!\n\n")
            break


if __name__ == '__main__':
    main() #start the deal hunt!