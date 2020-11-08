from bs4 import BeautifulSoup
import requests
import os
import datetime
import sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath("filehandler.py"))))
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
    print("\n"*30) #just in case

def printFirstPage(isFile = False):
    dealstuff = []
    deal, link, cost = frontpage()
    #clearScreen()
    for item in range(len(deal)): 
        if deal[item].replace(" ", "") != "":
            if isFile:
                dealstuff.append("| Deal | " + deal[item] + " | " + cost[item] + " | " + link[item] + " |")
            else:
                print("| Deal | " + deal[item] + " | " + cost[item] + " | " + link[item] + " |")
                print("=----<=>----=")
    return dealstuff

def frontpage():
    sickDeals, sickLinks, sickPrices = [], [], []
    siteOG = BeautifulSoup(requests.get("https://slickdeals.net").content, 'html.parser').find_all("div", {"class" : "fpItem"})
    for i in range(len(siteOG)):
        site = siteOG[i].find("div", {"class" : "itemImageLink"})
        deals = site.find_all("a", href=True)#find every deal per every site
        for deal in deals:
            sickDeals.append(deal.get_text()) #from every deal get the text
            sickLinks.append(deal["href"].replace("/f/", "https://slickdeals.net/f/").replace("/coupons/", "https://slickdeals.net/coupons/"))

        site = siteOG[i].find("div", id = lambda x: "itemPrice" in x)

        print(site)

        sickPrices.append(site.get_text().replace("  ", ""))
        

    return sickDeals, sickLinks, sickPrices #give back the array
    
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

