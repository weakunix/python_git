from bs4 import BeautifulSoup
import requests
import os
import datetime
from data import filehandler
import math

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

def query(query):
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

def main():
    printFirstPage()
    if datetime.datetime.now().timestamp() - float(filehandler.yamlload("./data/settings.yaml")["LastLog"]) > 8.64e+7: #if a day has passed then show frontpage deals
        with open("./savedlist/deal_of_"+str(datetime.datetime.now()).replace(" ","_")+".txt", "w+") as f:
            for timedDeal in printFirstPage(True):
                f.write(timedDeal + "\n")
    filehandler.yaml_it("./data/settings.yaml", "LastLog", str(datetime.datetime.now().timestamp())) #stamp now login time


if __name__ == '__main__':
    main() #start the deal hunt!