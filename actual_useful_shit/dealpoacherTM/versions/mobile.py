import mobileWidget
import json
import essencials
import re
import html
from bs4 import BeautifulSoup
import io

def main():
    deal, link = essencials.frontpage()
    SHORTCUTS = [{"title":"Search for deals","url":"pythonista3://","color": "#5e96ff"}]
    for item in range(len(deal) if len(deal) == len(link) else len("")):
        if deal[item] != "" and link[item] != "":
            deal[item] = re.sub("&(%s);", "", deal[item])
            print(deal[item])
            SHORTCUTS.append({"title":str(BeautifulSoup(deal[item])), "url": str((link[item])), "color": "#5e96ff"})
    with open("mobilestored.txt","w+", encode='utf-8') as f:
        f.write(str(SHORTCUTS))
    mobileWidget.main()

if __name__ == "__main__":
    main()