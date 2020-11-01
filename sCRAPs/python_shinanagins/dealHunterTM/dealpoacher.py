from bs4 import BeautifulSoup
import requests
import re

def query(query):
    return #return the site queried

def frontpage():
    sickDeals, sickLinks = [], []
    site = BeautifulSoup(requests.get("https://slickdeals.net").content, 'html.parser').find_all("div", {"class" : "itemImageLink"})
    for i in range(len(site)):
        deals = site[i].find_all("a", href=True)#find every deal per every site
        for deal in deals:
            sickDeals.append(deal.get_text()) #from every deal get the text
            sickLinks.append(deal["href"].replace("/f/", "https://slickdeals.net/f/"))
    return sickDeals, sickLinks #give back the array

def main():
    deal, link = frontpage()
    for item in range(len(deal)):
        print("Deal! " + deal[item] + " link: " + link[item])

if __name__ == '__main__':
    main() #start the deal hunt!